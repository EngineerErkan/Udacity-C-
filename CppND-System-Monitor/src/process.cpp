#include <unistd.h>
#include <cctype>
#include <sstream>
#include <vector>
#include <iostream>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) {
  pid2 = pid;
  cpu_util = Process::CpuUtilization();
  cmd = LinuxParser::Command(pid2);
}

// TODO: Return this process's ID
int Process::Pid() { return pid2; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
  long int Hz = sysconf(_SC_CLK_TCK);
  total_time = LinuxParser::ActiveJiffies(pid2)/ Hz; 
  seconds = LinuxParser::UpTime(pid2);
  return total_time/seconds;}

// TODO: Return the command that generated this process
string Process::Command() { return  LinuxParser::Command(pid2); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid2); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid2); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid2); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
  return cpu_util > a.cpu_util; 
}