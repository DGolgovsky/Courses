#include <uv.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

uv_tcp_t server;
uv_loop_t *loop;

void alloc_buffer_cb(uv_handle_t *handle, size_t size, uv_buf_t *buf)
{
    buf->base = (char *)malloc(size);
    buf->len = size;
    // return uv_buf_init((char *)malloc(size), size);
}

void read_cb(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf)
{
    uv_write_t *req = (uv_write_t *)malloc(sizeof(uv_write_t));
    if (nread < 0) {
        if ((nread & UV_EOF) != 0)
            fprintf(stderr, "Error on reading client stream: UV_EOF.\n");
        uv_close((uv_handle_t *) stream, NULL);
    }

    uv_buf_t buf_write;
    buf_write.base = (char *)malloc(nread);
    buf_write.len = nread;
    memcpy(buf_write.base, buf->base, nread);

    int r = uv_write(req, stream, &buf_write, 1, NULL);
    free(buf_write.base);

    if (r < 0)
        fprintf(stderr, "Error on writing client stream: %s.\n", r);

    free(buf->base);
}

void connection_cb(uv_stream_t *server, int status)
{
    uv_tcp_t *client = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));

    if (status < 0)
        fprintf(stderr, "Error on listening: %s.\n", status);

    uv_tcp_init(loop, client);
    if (uv_accept(server, (uv_stream_t *) client) == 0) {
        int r = uv_read_start((uv_stream_t *) client,
                alloc_buffer_cb,
                read_cb);
        if (r < 0)
            fprintf(stderr, "Error on reading client stream: %s.\n", r);
    } else {
        uv_close((uv_handle_t *) client, NULL); /* close client stream on error */
    }    
}

int main(int argc, char **argv)
{
    loop = uv_default_loop();

    struct sockaddr_in addr;
    uv_ip4_addr("0.0.0.0", 12345, &addr);

    uv_tcp_init(loop, &server);
    uv_tcp_bind(&server, (const struct sockaddr *)&addr, 0); // 0 == IPv4

    int r = uv_listen((uv_stream_t *)&server, 128, connection_cb);
    if (r < 0)
        return fprintf(stderr, "Error on listening: %s.\n", r);
    
    return uv_run(loop, UV_RUN_DEFAULT);
}
