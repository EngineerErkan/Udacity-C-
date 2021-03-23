#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return version + " " + kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string line;
  string key;
  float value;
  float Mtotal, Mfree;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") {
          Mtotal = value;
        }
        if (key == "MemFree:") {
          Mfree = value;
          return (Mtotal - Mfree) / Mtotal;
        }
      }
    }
  }
  return 0.0;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string line;
  long uptime;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }
  return uptime;
}


// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  string value, line;
  long total_clk;
  vector<string> stat_list;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while (linestream >> value) {
			stat_list.push_back(value);
        }
    }
  long int utime{std::stol(stat_list[13])};
  long int stime{std::stol(stat_list[14])};
  long int cutime{std::stol(stat_list[15])};
  long int cstime{std::stol(stat_list[16])};
  total_clk = (utime + stime + cutime + cstime);
  return total_clk;}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  vector<string> cpu_fields{"0", "0", "0", "0", "0", "0", "0", "0"};
  string line;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line); 
    std::istringstream linestream(line);
    if(linestream >> value){
      int i = 0;
      while(linestream >> value){
        if(i > 7){
          break;
        } 
        cpu_fields[i] = value;
        ++i;
      }
    }
  }
  return cpu_fields;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  int num_total_processes;
  string key, value, line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          num_total_processes = stoi(value);
        }
      }
    }
  }
  return num_total_processes;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string key, value;
  string line;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") return stoi(value);
      }
    }
  }
  return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string line, command;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
  }
  return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string key, value, unit, line;
  string ram;
  int vmsize;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value >> unit) {
        if (key == "VmSize:") {
          vmsize = stoi(value);
          vmsize = vmsize / 1024;
          ram = to_string(vmsize);
        }
      }
    }
  }
  return ram;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string line;
  string key;
  int value;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:") {
          return std::to_string(value);
        }
      }
    }
  }
  return string("0");
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string usr, passwd, uid, line;
  string uid_ = LinuxParser::Uid(pid);
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (std::getline(stream, line)){
        std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
    	while (linestream >> usr >> passwd >> uid) {
               if (uid==uid_){
                return usr;
               }
        	}
      	}
    }
  return string();
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string value, line;
  long int starttime, uptime;
  vector<string> stat_list;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while (linestream >> value) {
			stat_list.push_back(value);
        }
    }
  starttime = std::stol(stat_list[21])/sysconf(_SC_CLK_TCK);
  uptime =  LinuxParser::UpTime() - starttime;
  return uptime;
}