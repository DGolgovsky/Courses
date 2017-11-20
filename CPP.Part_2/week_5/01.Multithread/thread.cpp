// Сразу же начинает вычислять функцию
// Игнорирует возврашаемое значение

int res = 0;
std::thread t([&res](){res = doAsyncWork();});
t.join();

// Метод join() блокирует поток, пока его выполнение не завершится
// Метод detach() отключает поток от объекта, разрывает связь
// При вызове деструктора подключаемого потока программа завершается
// Исключения не могут покидать пределы потока
// native_handle() возвращает дескриптор потока
