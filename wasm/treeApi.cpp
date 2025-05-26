#include <emscripten/bind.h>
#include <emscripten/val.h>
#include "../inc/AVLTree.hpp"
#include "../inc/binaryTree.hpp"
#include "../types/complex.hpp"
#include "../types/person.hpp"

using namespace emscripten;

// value_object для Complex и Person через геттеры/сеттеры
EMSCRIPTEN_BINDINGS(tree_types)
{
    value_object<Complex>("Complex")
        .field("re", &Complex::getReal, &Complex::setReal)
        .field("im", &Complex::getImag, &Complex::setImag);

    value_object<Person>("Person")
        .field("name", &Person::getName, &Person::setName)
        .field("age", &Person::getAge, &Person::setAge);
}

// --- INT ---

// AVLTree<int>
void avl_insert_int(AVLTree<int> &t, int v) { t.insert(v); }
void avl_remove_int(AVLTree<int> &t, int v) { t.remove(v); }
bool avl_find_int(AVLTree<int> &t, int v) { return t.search(v) != nullptr; }
bool avl_has_value_int(AVLTree<int> &t, int v) { return t.hasValue(v); }
std::string avl_serialize_int(AVLTree<int> &t, std::string order) { return t.serialize(order); }
void avl_clear_int(AVLTree<int> &t) { t.clear(); }
bool avl_empty_int(AVLTree<int> &t) { return t.isEmpty(); }
int avl_height_int(AVLTree<int> &t) { return t.getHeight(t.getRoot()); }
bool avl_isBalanced_int(AVLTree<int> &t) { return t.isBalanced(); }
int avl_min_int(AVLTree<int> &t) { return t.getMin(); }
int avl_max_int(AVLTree<int> &t) { return t.getMax(); }
void avl_make_threaded_int(AVLTree<int> &t, std::string order) { t.makeThreaded(order); }
BinaryTree<int>* avl_subtree_int(AVLTree<int> &t, int v) { return t.subtree(v); }
bool avl_contains_subtree_int(AVLTree<int> &t, AVLTree<int> &other) { return t.containsSubtree(other); }
BinaryTree<int>* avl_find_by_path_int(AVLTree<int> &t, std::string path) { return t.findByPath(path); }
AVLTree<int> *make_avl_int() { return new AVLTree<int>(); }

// BinaryTree<int>
void bin_insert_int(BinaryTree<int> &t, int v) { t.insert(v, t.getRoot()); }
void bin_remove_int(BinaryTree<int> &t, int v) { t.remove(v); }
bool bin_find_int(BinaryTree<int> &t, int v) { return t.search(v) != nullptr; }
bool bin_has_value_int(BinaryTree<int> &t, int v) { return t.hasValue(v); }
std::string bin_serialize_int(BinaryTree<int> &t, std::string order) { return t.serialize(order); }
void bin_clear_int(BinaryTree<int> &t) { t.clear(); }
bool bin_empty_int(BinaryTree<int> &t) { return t.isEmpty(); }
int bin_height_int(BinaryTree<int> &t) { return t.getHeight(); }
void bin_balance_int(BinaryTree<int> &t) { t.balance(); }
int bin_min_int(BinaryTree<int> &t) { return t.getMin(); }
int bin_max_int(BinaryTree<int> &t) { return t.getMax(); }
bool bin_is_balanced_int(BinaryTree<int> &t) { return t.isBalanced(); }
void bin_make_threaded_int(BinaryTree<int> &t, std::string order) { t.makeThreaded(order); }
BinaryTree<int>* bin_subtree_int(BinaryTree<int> &t, int v) { return t.subtree(v); }
bool bin_contains_subtree_int(BinaryTree<int> &t, BinaryTree<int> &other) { return t.containsSubtree(other); }
BinaryTree<int>* bin_find_by_path_int(BinaryTree<int> &t, std::string path) { return t.findByPath(path); }

// Functional operations for Int
int bin_reduce_int(BinaryTree<int> &t, emscripten::val reducer, int initial) {
    return t.reduce([&](int a, int b) -> int {
        return reducer(a, b).as<int>();
    }, initial);
}

BinaryTree<int>* bin_apply_int(BinaryTree<int> &t, emscripten::val mapper) {
    return new BinaryTree<int>(t.apply([&](int val) -> int {
        return mapper(val).as<int>();
    }));
}

BinaryTree<int>* bin_where_int(BinaryTree<int> &t, emscripten::val predicate) {
    return new BinaryTree<int>(t.where([&](int val) -> bool {
        return predicate(val).as<bool>();
    }));
}

BinaryTree<int> *make_bin_int() { return new BinaryTree<int>(); }

// --- COMPLEX ---

void avl_insert_complex(AVLTree<Complex> &t, Complex v) { t.insert(v); }
void avl_remove_complex(AVLTree<Complex> &t, Complex v) { t.remove(v); }
bool avl_find_complex(AVLTree<Complex> &t, Complex v) { return t.search(v) != nullptr; }
std::string avl_serialize_complex(AVLTree<Complex> &t, std::string order) { return t.serialize(order); }
void avl_clear_complex(AVLTree<Complex> &t) { t.clear(); }
bool avl_empty_complex(AVLTree<Complex> &t) { return t.isEmpty(); }
int avl_height_complex(AVLTree<Complex> &t) { return t.getHeight(t.getRoot()); }
bool avl_isBalanced_complex(AVLTree<Complex> &t) { return t.isBalanced(); }
Complex avl_min_complex(AVLTree<Complex> &t) { return t.getMin(); }
Complex avl_max_complex(AVLTree<Complex> &t) { return t.getMax(); }
AVLTree<Complex> *make_avl_complex() { return new AVLTree<Complex>(); }
BinaryTree<Complex>* avl_find_by_path_complex(AVLTree<Complex> &t, std::string path) { return t.findByPath(path); }

void bin_insert_complex(BinaryTree<Complex> &t, Complex v) { t.insert(v, t.getRoot()); }
void bin_remove_complex(BinaryTree<Complex> &t, Complex v) { t.remove(v); }
bool bin_find_complex(BinaryTree<Complex> &t, Complex v) { return t.search(v) != nullptr; }
std::string bin_serialize_complex(BinaryTree<Complex> &t, std::string order) { return t.serialize(order); }
void bin_clear_complex(BinaryTree<Complex> &t) { t.clear(); }
bool bin_empty_complex(BinaryTree<Complex> &t) { return t.isEmpty(); }
int bin_height_complex(BinaryTree<Complex> &t) { return t.getHeight(); }
Complex bin_min_complex(BinaryTree<Complex> &t) { return t.getMin(); }
Complex bin_max_complex(BinaryTree<Complex> &t) { return t.getMax(); }
BinaryTree<Complex>* bin_find_by_path_complex(BinaryTree<Complex> &t, std::string path) { return t.findByPath(path); }
BinaryTree<Complex> *make_bin_complex() { return new BinaryTree<Complex>(); }

// Functional operations for Complex
Complex bin_reduce_complex(BinaryTree<Complex> &t, emscripten::val reducer, Complex initial) {
    return t.reduce([&](Complex a, Complex b) -> Complex {
        val result = reducer(val(a), val(b));
        return Complex(result["re"].as<double>(), result["im"].as<double>());
    }, initial);
}

BinaryTree<Complex>* bin_apply_complex(BinaryTree<Complex> &t, emscripten::val mapper) {
    return new BinaryTree<Complex>(t.apply([&](Complex value) -> Complex {
        val result = mapper(val(value));
        return Complex(result["re"].as<double>(), result["im"].as<double>());
    }));
}

BinaryTree<Complex>* bin_where_complex(BinaryTree<Complex> &t, emscripten::val predicate) {
    return new BinaryTree<Complex>(t.where([&](Complex val) -> bool {
        return predicate(val).as<bool>();
    }));
}

// --- PERSON ---

void avl_insert_person(AVLTree<Person> &t, Person v) { t.insert(v); }
void avl_remove_person(AVLTree<Person> &t, Person v) { t.remove(v); }
bool avl_find_person(AVLTree<Person> &t, Person v) { return t.search(v) != nullptr; }
std::string avl_serialize_person(AVLTree<Person> &t, std::string order) { return t.serialize(order); }
void avl_clear_person(AVLTree<Person> &t) { t.clear(); }
bool avl_empty_person(AVLTree<Person> &t) { return t.isEmpty(); }
int avl_height_person(AVLTree<Person> &t) { return t.getHeight(t.getRoot()); }
bool avl_isBalanced_person(AVLTree<Person> &t) { return t.isBalanced(); }
Person avl_min_person(AVLTree<Person> &t) { return t.getMin(); }
Person avl_max_person(AVLTree<Person> &t) { return t.getMax(); }
BinaryTree<Person>* avl_find_by_path_person(AVLTree<Person> &t, std::string path) { return t.findByPath(path); }
AVLTree<Person> *make_avl_person() { return new AVLTree<Person>(); }

void bin_insert_person(BinaryTree<Person> &t, Person v) { t.insert(v, t.getRoot()); }
void bin_remove_person(BinaryTree<Person> &t, Person v) { t.remove(v); }
bool bin_find_person(BinaryTree<Person> &t, Person v) { return t.search(v) != nullptr; }
std::string bin_serialize_person(BinaryTree<Person> &t, std::string order) { return t.serialize(order); }
void bin_clear_person(BinaryTree<Person> &t) { t.clear(); }
bool bin_empty_person(BinaryTree<Person> &t) { return t.isEmpty(); }
int bin_height_person(BinaryTree<Person> &t) { return t.getHeight(); }
Person bin_min_person(BinaryTree<Person> &t) { return t.getMin(); }
Person bin_max_person(BinaryTree<Person> &t) { return t.getMax(); }
BinaryTree<Person>* bin_find_by_path_person(BinaryTree<Person> &t, std::string path) { return t.findByPath(path); }
BinaryTree<Person> *make_bin_person() { return new BinaryTree<Person>(); }

// Functional operations for Person
Person bin_reduce_person(BinaryTree<Person> &t, emscripten::val reducer, Person initial) {
    return t.reduce([&](Person a, Person b) -> Person {
        try {
            val result = reducer(val(a), val(b));
            
            // Safe string conversion
            std::string name;
            if (result["name"].isString()) {
                name = result["name"].as<std::string>();
            } else if (result["name"].isUndefined() || result["name"].isNull()) {
                name = "";
            } else {
                // Convert to string via JavaScript toString()
                name = result["name"].call<std::string>("toString");
            }
            
            int age = result["age"].isNumber() ? 
                     result["age"].as<int>() : 
                     0;
                     
            return Person(name, age);
        } catch (const std::exception& e) {
            std::cerr << "Error in reduce function: " << e.what() << std::endl;
            return a; // Return first argument on error
        }
    }, initial);
}

BinaryTree<Person>* bin_apply_person(BinaryTree<Person> &t, emscripten::val mapper) {
    return new BinaryTree<Person>(t.apply([&](Person value) -> Person {
        try {
            val result = mapper(val(value));
            
            // Safe string conversion
            std::string name;
            if (result["name"].isString()) {
                name = result["name"].as<std::string>();
            } else if (result["name"].isUndefined() || result["name"].isNull()) {
                name = "";
            } else {
                // Convert to string via JavaScript toString()
                name = result["name"].call<std::string>("toString");
            }
            
            int age = result["age"].isNumber() ? 
                     result["age"].as<int>() : 
                     0;
                     
            return Person(name, age);
        } catch (const std::exception& e) {
            std::cerr << "Error in apply mapper: " << e.what() << std::endl;
            return value; // Return original value on error
        }
    }));
}

BinaryTree<Person>* bin_where_person(BinaryTree<Person> &t, emscripten::val predicate) {
    return new BinaryTree<Person>(t.where([&](Person val) -> bool {
        // Use try/catch to handle any potential conversion errors
        try {
            return predicate(val).as<bool>();
        } catch (const std::exception& e) {
            std::cerr << "Error in predicate: " << e.what() << std::endl;
            return false;
        }
    }));
}

// --- BINDINGS ---

EMSCRIPTEN_BINDINGS(tree_module)
{
    // AVLTree<int>
    class_<AVLTree<int>>("AVLTreeInt")
        .constructor<>()
        .function("insert", &avl_insert_int)
        .function("remove", &avl_remove_int)
        .function("find", &avl_find_int)
        .function("hasValue", &avl_has_value_int)
        .function("serialize", &avl_serialize_int)
        .function("clear", &avl_clear_int)
        .function("empty", &avl_empty_int)
        .function("height", &avl_height_int)
        .function("isBalanced", &avl_isBalanced_int)
        .function("getMin", &avl_min_int)
        .function("getMax", &avl_max_int)
        .function("makeThreaded", &avl_make_threaded_int)
        .function("containsSubtree", &avl_contains_subtree_int)
        .function("findByPath", &avl_find_by_path_int, allow_raw_pointers());
    function("make_avl_int", &make_avl_int, allow_raw_pointers());
    function("subtree_avl_int", &avl_subtree_int, allow_raw_pointers());

    // BinaryTree<int>
    class_<BinaryTree<int>>("BinaryTreeInt")
        .constructor<>()
        .function("insert", &bin_insert_int)
        .function("remove", &bin_remove_int)
        .function("find", &bin_find_int)
        .function("hasValue", &bin_has_value_int)
        .function("serialize", &bin_serialize_int)
        .function("clear", &bin_clear_int)
        .function("empty", &bin_empty_int)
        .function("height", &bin_height_int)
        .function("balance", &bin_balance_int)
        .function("getMin", &bin_min_int)
        .function("getMax", &bin_max_int)
        .function("isBalanced", &bin_is_balanced_int)
        .function("makeThreaded", &bin_make_threaded_int)
        .function("containsSubtree", &bin_contains_subtree_int)
        .function("findByPath", &bin_find_by_path_int, allow_raw_pointers())
        .function("reduce", &bin_reduce_int)
        .function("apply", &bin_apply_int, allow_raw_pointers())
        .function("where", &bin_where_int, allow_raw_pointers());
    function("make_bin_int", &make_bin_int, allow_raw_pointers());
    function("subtree_int", &bin_subtree_int, allow_raw_pointers());

    // AVLTree<Complex>
    class_<AVLTree<Complex>>("AVLTreeComplex")
        .constructor<>()
        .function("insert", &avl_insert_complex)
        .function("remove", &avl_remove_complex)
        .function("find", &avl_find_complex)
        .function("serialize", &avl_serialize_complex)
        .function("clear", &avl_clear_complex)
        .function("empty", &avl_empty_complex)
        .function("height", &avl_height_complex)
        .function("isBalanced", &avl_isBalanced_complex)
        .function("getMin", &avl_min_complex)
        .function("getMax", &avl_max_complex)
        .function("findByPath", &avl_find_by_path_complex, allow_raw_pointers());
    function("make_avl_complex", &make_avl_complex, allow_raw_pointers());

    // BinaryTree<Complex>
    class_<BinaryTree<Complex>>("BinaryTreeComplex")
        .constructor<>()
        .function("insert", &bin_insert_complex)
        .function("remove", &bin_remove_complex)
        .function("find", &bin_find_complex)
        .function("serialize", &bin_serialize_complex)
        .function("clear", &bin_clear_complex)
        .function("empty", &bin_empty_complex)
        .function("height", &bin_height_complex)
        .function("getMin", &bin_min_complex)
        .function("getMax", &bin_max_complex)
        .function("findByPath", &bin_find_by_path_complex, allow_raw_pointers())
        .function("reduce", &bin_reduce_complex)
        .function("apply", &bin_apply_complex, allow_raw_pointers())
        .function("where", &bin_where_complex, allow_raw_pointers());
    function("make_bin_complex", &make_bin_complex, allow_raw_pointers());

    // AVLTree<Person>
    class_<AVLTree<Person>>("AVLTreePerson")
        .constructor<>()
        .function("insert", &avl_insert_person)
        .function("remove", &avl_remove_person)
        .function("find", &avl_find_person)
        .function("serialize", &avl_serialize_person)
        .function("clear", &avl_clear_person)
        .function("empty", &avl_empty_person)
        .function("height", &avl_height_person)
        .function("isBalanced", &avl_isBalanced_person)
        .function("getMin", &avl_min_person)
        .function("getMax", &avl_max_person)
        .function("findByPath", &avl_find_by_path_person, allow_raw_pointers());
    function("make_avl_person", &make_avl_person, allow_raw_pointers());

    // BinaryTree<Person>
    class_<BinaryTree<Person>>("BinaryTreePerson")
        .constructor<>()
        .function("insert", &bin_insert_person)
        .function("remove", &bin_remove_person)
        .function("find", &bin_find_person)
        .function("serialize", &bin_serialize_person)
        .function("clear", &bin_clear_person)
        .function("empty", &bin_empty_person)
        .function("height", &bin_height_person)
        .function("getMin", &bin_min_person)
        .function("getMax", &bin_max_person)
        .function("findByPath", &bin_find_by_path_person, allow_raw_pointers())
        .function("reduce", &bin_reduce_person)
        .function("apply", &bin_apply_person, allow_raw_pointers())
        .function("where", &bin_where_person, allow_raw_pointers());
    function("make_bin_person", &make_bin_person, allow_raw_pointers());
}