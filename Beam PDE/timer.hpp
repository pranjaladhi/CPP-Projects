//Timer file to time the process of the solver to compare between non-turbo and turbo modes
#include <chrono>
#include <cassert>

class Timer
{
private:
    std::chrono::time_point<std::chrono::system_clock> tstart_;
    std::chrono::time_point<std::chrono::system_clock> tend_;

public:
    void Start() { tstart_ = std::chrono::system_clock::now();};
    void Stop()  {   tend_ = std::chrono::system_clock::now();};
    double ElapsedTime()
    {
        return(std::chrono::duration_cast<std::chrono::microseconds>(tend_ - tstart_).count()/1000000.0);
    }
};
