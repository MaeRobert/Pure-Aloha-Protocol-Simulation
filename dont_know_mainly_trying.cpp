#include <vector>
#include "TP4_exo2.hpp"

class System{
    public:
    // The total number of packets that we want to send.
    int number_of_packets_;

    // The time that it takes to transmit a packet.
    float transmition_duration_;

    // This is a tab, such that if we have n packets to transmit, 
    // the tab will be of length n, with tab[i] being the time (a 
    // float) at wich the packet number i will be sent. 
    std::vector<float> transmition_times_;

    // The number of successufuly transmitted packets.
    int successful_transmitions_;

    // A function to initialize transmition_times, using 
    // our random exponential generator.
    void initialisation_(int number_of_packets, float transmition_duration, float lambda)
    {
        this->number_of_packets_ = number_of_packets;
        this->transmition_duration_ = transmition_duration;
        this->successful_transmitions_ = 0;
        float time = 0; // The time at which the simulation starts
        // We fill transmition_times_.
        for(int i = 0 ; i < number_of_packets ; i++){ 
            time = time + exponential_random_generator(lambda); 
            this->transmition_times_.push_back(time);
        }
    };

    // Checks if we can send a packet
    // Rq: as we use transmition_times_, we do not 
    // have to implement the different states (free, one packet
    // arriving, multiple packets arriving) that the channel 
    // can take, but it still is the idea behind.
    bool send_packet_(int i)
    {
        // The idea is to check wether or not 
        // a packet is send in the same "time interval"
        // (of length 2*transmition_duration_) than 
        // the packet in the i^th case of the table.

        // We check the packets that were sent before this one.
        if( (i - 1 >= 0) && transmition_times_[i - 1] >= transmition_times_[i] - transmition_duration_){
            return false;
        }
        // We check the packets sent after this one.
        if( (i + 1 <= number_of_packets_ - 1) && transmition_times_[i] + transmition_duration_ >= transmition_times_[i + 1]){
            return false;
        }
        // If we are not in the previous cases, then the packet 
        // can be sent!
        this->successful_transmitions_ ++;
        return true;
    };

};


float simulation(int number_of_packets, float lambda, int transmition_duration)
{
    System our_system;
    our_system.initialisation_(number_of_packets, transmition_duration, lambda);

    for(int i = 0 ; i < number_of_packets ; i ++){
        our_system.send_packet_(i);
    }
    
    return our_system.successful_transmitions_*((float) our_system.transmition_duration_)/our_system.transmition_times_[number_of_packets - 1];
}


int main()
{
    // Initialization of random seed.
    srand (time(NULL));

    int number_of_packets = 100000;
    int transmition_duration = 1;
    int number_of_lambdas = 1000;
    float lambda;
    float max_lambda = 3;
    float successes;
    FILE *save = fopen("res.txt", "w+");

    for(int i = 1 ; i < number_of_lambdas + 1 ; i++){
        lambda = max_lambda*((float) i)/((float) number_of_lambdas);
        successes = simulation(number_of_packets, lambda, transmition_duration);

        fprintf(save, "%f %f\n", lambda, successes);
    }


    fclose(save);

    return 0;
}
