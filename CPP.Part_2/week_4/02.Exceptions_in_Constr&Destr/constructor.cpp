struct Database {
    explicit Database(string const& uri) {
        if (!connect(uri))
            throw ConnectionError(uri); // Abort object creation
    }
    ~Database() {
        disconnect();
    }
    // ...
};

int main()
{
    try {
        Database * db = new Database("db.local"); // Free mem if except
        db->dump("db-local-dump.sql");
        delete db;
    } catch (std::exception const& e) {
        std::cerr << e.what() << '\n';
    }
}

