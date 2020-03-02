/*
 * Вам требуется реализовать функцию,
 * которая принимает на вход два указателя на базовый класс Expression,
 * и возвращает true, если оба указателя указывают на самом деле на объекты одного и того же класса,
 * и false в противном случае
 * (т.е. если оба указателя указывают на BinaryOperation, то возвращается true,
 * а если один из них указывает на Number, а второй на BinaryOperation, то false).
 *
 * Реализуйте её при помощи typeid.
*/

#include <typeinfo>

bool check_equals(Expression const *left, Expression const *right)
{
    /* http://en.cppreference.com/w/cpp/language/typeid
     * There is no guarantee that the same std::type_info instance 
     * will be referred to by all evaluations of the typeid expression 
     * on the same type, although std::type_info::hash_code of those 
     * type_info objects would be identical, as would be their std::type_index.
     */
    
    /* http://en.cppreference.com/w/cpp/types/type_info/hash_code
     * type_info objects referring to different types may have the same hash_code 
     * (although the standard recommends that implementations avoid this as much as possible), 
     * and hash_code for the same type can change between invocations of the same program.
     */
    
    // main.cpp:44:26: error: 'const class std::type_info' has no member named 'hash_code'
    //return typeid(*left).hash_code() == typeid(*right).hash_code();

    return (typeid(*left) == typeid(*right));
}
