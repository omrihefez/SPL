#ifndef TRAINER_H_
#define TRAINER_H_

#include <vector>
#include "Customer.h"
#include "Workout.h"

typedef std::pair<int, Workout> OrderPair;

class Trainer{
public:
    Trainer(int t_capacity);
    Trainer(const Trainer &other); // copy constructor
    void copy(std::vector<Customer*> other_customersList, std::vector<OrderPair> other_orderList );
    Trainer& operator=(Trainer& other); // copy assignment operator
    ~Trainer(); // destructor
    Trainer(Trainer&& other); // move constructor
    void clear();
    Trainer& operator=(Trainer &&other); // move assignment operator
    int getCapacity() const;
    void addCustomer(Customer* customer);
    void removeCustomer(int id);
    Customer* getCustomer(int id);
    std::vector<Customer*>& getCustomers();
    std::vector<OrderPair>& getOrders();
    std::vector<OrderPair> removeOrdersOfCustomerById(int customerId);
    void addOrdersAfterMove(std::vector<OrderPair> v);
    void order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options);
    void openTrainer();
    void closeTrainer();
    int getSalary();
    bool isOpen();
private:
    int id;
    int capacity;
    bool open;
    int salary;
    int origCapacity;
    std::vector<Customer*> customersList;
    std::vector<OrderPair> orderList; //A list of pairs for each order for the trainer - (customer_id, Workout)
};


#endif