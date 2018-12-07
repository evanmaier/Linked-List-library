/* linkedlist.hpp
   CSC 116 - Fall 2018

   Evan Maier - 11/04/2018
   V00891872
   linked list library
*/

#include <functional>
#include <stdexcept>
#include <memory>
#include <initializer_list>
#include <iostream>

//Important note: You may add other #include directives, but you are NOT
//permitted to use or include ANY of the standard collections, including
//std::list, std::vector, std::set, std::map, std::unordered_set, 
//std::forward_list, std::unordered_map, std::array 
//(or any derivatives thereof, such as std::queue)
//If you do so, your assignment will receive a mark of zero.
//You ARE permitted to use the specialized std::initializer_list collection,
//as indicated below in the constructor.

template<typename T>
class LinkedList{
public:
    /* Default constructor:
       Construct the list to be empty (size = 0)
    */
    LinkedList(){
        head = nullptr;
    }
    /* Initializer list constructor:
       Construct the list to contain all of the elements in the
       provided initializer list. Recall that you can use a for-each
       loop to iterate over initializer_list objects. */
    LinkedList( std::initializer_list<T> initial_contents ){

        ListNodePtr node_ptr; 
        
        for( auto it = initial_contents.begin(); it != initial_contents.end(); it++ )
        {
            if( it == initial_contents.begin() ) //first element
            {
                node_ptr = std::make_shared<ListNode>(*it,nullptr);
                head = node_ptr;
            }
            else if( it+1 != initial_contents.end() ) //middle elements
            {
                node_ptr -> next = std::make_shared<ListNode>(*it,nullptr);
                node_ptr = node_ptr -> next;
            }
            else //last element
            {
                node_ptr -> next = std::make_shared<ListNode>(*it,nullptr);
                node_ptr = node_ptr -> next;
            }
        }
    }
    /* Copy constructor:
       Construct the list to contain all of the elements in the provided
       other list. Note that a "deep copy" is needed, such that when the 
       operation completes there are two separate, independent lists.
    */
    LinkedList( LinkedList<T> const& other_list ){
        auto node_ptr = head;
        auto other_node_ptr = other_list.head;
        if(!other_list.is_empty())
        {
            node_ptr = std::make_shared<ListNode>(other_node_ptr -> value,nullptr);
            head = node_ptr;
            other_node_ptr = other_node_ptr -> next;
            while(other_node_ptr != nullptr)
            {
                node_ptr -> next = std::make_shared<ListNode>(other_node_ptr -> value,nullptr);
                other_node_ptr = other_node_ptr -> next;
                node_ptr = node_ptr -> next;
            }
        }

    }
    /* Destructor */
    ~LinkedList(){
        /* Your code here */
    }

    /* is_empty()
       Returns true if the list contains zero elements and false otherwise.
    */
    bool is_empty() const{
        if(head == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /* size()
       Returns the number of elements in the list.
    */
    unsigned int size() const{
        if(!is_empty())
        {
            auto node_ptr = head;
            int counter = 1;
            while(node_ptr -> next != nullptr)
            {
                counter++;
                node_ptr = node_ptr -> next;
            }
            return counter;
        }
        else 
        {
            return 0;
        }
    }


    /* first() - Version 1
       If the list has at least one element, returns a reference to the first
       element (such that the result can be modified by the caller).
       If the list has zero elements, throw an exception of type std::runtime_error.
    */
    T& first(){
        if(!is_empty())
        {
            T& first_elem = head -> value;
            return first_elem; 
        }
        else
        {
            throw std::runtime_error("empty list");
        }
    }

    /* first() - Version 2
       If the list has at least one element, returns a const reference to the
       first element.
       If the list has zero elements, throw an exception of type std::runtime_error.
    */
    T const& first() const {
        if(!is_empty())
        {
            T const& first_elem = head -> value;
            return first_elem; 
        }
        else
        {
            throw std::runtime_error("empty list");
        }
    }
    
    /* last() - Version 1
       If the list has at least one element, returns a reference to the last
       element (such that the result can be modified by the caller).
       If the list has zero elements, throw an exception of type std::runtime_error.
    */
    T& last(){
        if(!is_empty())
        {
            auto node_ptr = head;
            while(node_ptr -> next != nullptr)
            {
                node_ptr = node_ptr -> next;
            }
            T& last_elem = node_ptr -> value;
            return last_elem;
        }
        else
        {
            throw std::runtime_error("empty list");
        }
    }

    /* last() - Version 2
       If the list has at least one element, returns a const reference to the
       last element.
       If the list has zero elements, throw an exception of type std::runtime_error.
    */
    T const& last() const {
         if(!is_empty())
        {
            auto node_ptr = head;
            while(node_ptr -> next != nullptr)
            {
                node_ptr = node_ptr -> next;
            }
            T const& last_elem = node_ptr -> value;
            return last_elem;
        }
        else
        {
            throw std::runtime_error("empty list");
        }
    }
    


    /* push_front(value)
       Add a copy of the provided value to the list as the first element.
    */
    void push_front(T const& value){
        auto node_ptr = std::make_shared<ListNode>(value,nullptr);
        node_ptr -> next = head;
        head = node_ptr;
        //std::cout<<"pushed front "<<value<<std::endl;
    }
    
    /* push_front(value)
       Add a copy of the provided value to the list as the last element.
    */
    void push_back(T const& value){
        auto node_ptr = head;
        if(!is_empty())
        {
            while(node_ptr -> next != nullptr)
            {
                node_ptr = node_ptr -> next;
            }
        auto new_node_ptr = std::make_shared<ListNode>(value,nullptr); //create new node
        node_ptr -> next = new_node_ptr; //point previous last node to new node
        }
        else
        {
            push_front(value);
        }
       // std::cout<<"pushed back "<<value<<std::endl;
    }
    

    /* pop_front()
       If the list has at least one element, remove the first element and
       return a copy of its value.
       If the list has zero elements, throw an exception of type std::runtime_error.
    */
    T pop_front(){
        if(!is_empty())
        {
            T first_value = head -> value;
            head = head -> next;
            return first_value;
        }
        else
        {
            throw std::runtime_error("empty list"); 
        }
    }
    
    /* pop_back()
       If the list has at least one element, remove the last element and
       return a copy of its value.
       If the list has zero elements, throw an exception of type std::runtime_error.
    */
    T pop_back(){
        if(!is_empty())
        {
            auto node_ptr = head;
            if (node_ptr -> next == nullptr)
            {
                head = nullptr;
                return node_ptr -> value;
            }
            while(node_ptr -> next != nullptr && node_ptr -> next -> next != nullptr)
            {
                node_ptr = node_ptr -> next;
            }
            T last_value = node_ptr -> next -> value;
            node_ptr -> next = nullptr;
            return last_value;
        }
        else
        {
            throw std::runtime_error("empty list"); 
        }
    }
    
    /* contains(element)
       Return true if any element of the list is equal (using the == operator) to 
       the provided element. Return false otherwise.
    */
    bool contains(T const& element) const{
        auto node_ptr = head;
        if(!is_empty())
        {
            while(node_ptr != nullptr)
            {
                if( (node_ptr -> value) == element )
                {
                    return true;
                }
                node_ptr = node_ptr -> next;
            }
        }
        return false;
    }
    
    /* clear()
       Remove all elements from the list.
    */
    void clear(){
        while(!is_empty())
        {
            pop_back();
        }
    }
    
    /* operator==
       Return true if this list is equal to the provided other list.
       Two lists are considered equal if they have the same length and
       contain the same sequence of elements (in the same order). Use
       the == operator to compare individual elements to each other.
    */
    bool operator==(LinkedList<T> const& other_list) const{
        if(size() != other_list.size())
        {
            return false;
        }
        auto node_ptr = head;
        auto other_node_ptr = other_list.head;
        if(!is_empty())
        {
            while(node_ptr != nullptr)
            {
                if( (node_ptr -> value) == (other_node_ptr -> value) )
                {
                    return true;
                }
                other_node_ptr = other_node_ptr -> next;
                node_ptr = node_ptr -> next;
            }
        }
        return false;
    }
    
    /* operator!=
       Return true if this list is not equal to the provided other list.
       In this context, two lists are not equal if the operator== above
       returns false.
    */
    bool operator!=(LinkedList<T> const& other_list) const{
        if(*this == other_list)
        {
            return false;
        }
        return true;
    }
    

    /* operator=
       Set this list to be a copy of the provided other list.
       (If this list already contains any values, remove all of them first).
    */
    LinkedList<T>& operator=(LinkedList<T> const& other_list){
        if(!is_empty())
        {
            clear();
        }
        auto node_ptr = head;
        auto other_node_ptr = other_list.head;
        if(!other_list.is_empty())
        {
            node_ptr = std::make_shared<ListNode>(other_node_ptr -> value,nullptr);
            head = node_ptr;
            other_node_ptr = other_node_ptr -> next;
            while(other_node_ptr != nullptr)
            {
                node_ptr -> next = std::make_shared<ListNode>(other_node_ptr -> value,nullptr);
                other_node_ptr = other_node_ptr -> next;
                node_ptr = node_ptr -> next;
            }
        }
        return *this;
    }
    
    /* apply(func) - Version 1
       Given a function that takes a single argument (which is a reference to an 
       element), call that function on each element of this list (in forward 
       order). Note that since the element is passed by non-const reference, the 
       provided function has the ability to modify the elements of the list.
    */
    void apply( std::function< void(T&) > func ){
        auto node_ptr = head;
        if(!is_empty())
        {
            while(node_ptr != nullptr)
            {
                func(node_ptr -> value);
                node_ptr = node_ptr -> next;
            }
        }
    }
    
    /* apply(func) - Version 2
       Given a function that takes a single argument (which is a const reference 
       to an element), call that function on each element of this list (in 
       forward order).

       Note that the only difference between this and version 1 is that this
       is guaranteed not to modify the list elements (since the reference passed
       to the function is const). It will likely be possible to use almost
       identical code for this version as for version 1.
    */
    void apply( std::function< void(T const&) > func ) const{
        auto node_ptr = head;
        if(!is_empty())
        {
            while(node_ptr != nullptr)
            {
                func(node_ptr -> value);
                node_ptr = node_ptr -> next;
            }
        }
    }

    /* remove_where(func)
       Given a function which takes a list element and returns a boolean value, remove
       all elements of the list where the provided function returns true 
    */
    void remove_where( std::function< bool(T const&) > condition_function ){
        if(!is_empty())
        {
            auto node_ptr = head;
            while(node_ptr != nullptr && node_ptr -> next != nullptr)
            {
                if(condition_function(node_ptr -> next -> value))
                {
                    node_ptr -> next = node_ptr -> next -> next;
                }
                node_ptr = node_ptr -> next;
            }    
            if(condition_function(head -> value))
            {
                head = head -> next;
            }
        }
    }
    
    
    /* transform(func)
       Given a function that takes a single argument (which is a const reference 
       to an element of this list) and returns a value (of some type OutputType),
       call that function on each element of this list (in forward order), then
       add the result to a new list (of element type OutputType). Return the
       resulting list.
    */

    template<typename OutputType>
    LinkedList<OutputType> transform( std::function< OutputType(T const&) > transform_function ){
        LinkedList<OutputType> return_list;
        auto node_ptr = head;
        if(!is_empty())
        {
            while(node_ptr != nullptr)
            {
                return_list.push_back(transform_function(node_ptr -> value));
                node_ptr = node_ptr -> next;
            }
        }
        return return_list;
    }

    /* print values in list for testing purposes */

    void print()
    {
        auto node_ptr = head;
        std::cout<< node_ptr->value<<" ";
        while(node_ptr -> next != nullptr)
        {
            node_ptr = node_ptr -> next;
            std::cout<< node_ptr->value<<" ";
        }
        std::cout<<std::endl;
    }

private:

    /* Note that since ListNode is a struct (not a class), all of its members will be
       public by default. */
    struct ListNode;
    using ListNodePtr = std::shared_ptr<ListNode>;
    struct ListNode{
        ListNode(T const& val, ListNodePtr next_node) {
			value = val;
			next = next_node;
        }
        T value;
        ListNodePtr next;
    };

    ListNodePtr head;

    /* You may add other private members as needed. */


};