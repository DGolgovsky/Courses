int foo() {
    if (...) throw -1;
    if (...) throw 3.1415;
}

void bar(int a) {
    if (a == 0) throw string("Not my fault!");
}

int main() {
    try { bar(foo());
    } catch (string &s) {
        // only text
    } catch (int a) {
        // poor information
    } catch (double d) {
        // poor information
    } catch (...) {
        // no information
    }
}
