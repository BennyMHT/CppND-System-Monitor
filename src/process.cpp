#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
 
#include "process.h"

using std::string;
using std::to_string;
using std::vector;
using std::stof;
using std::stoi;
using std::stol;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
  string time;
  float utime, stime, cutime, cstime, starttime;
  int i = 1;
  std::ifstream stream("/proc/"+to_string(pid_)+"/stat");
  if(stream.is_open()) {
    while(stream >> time) {
      if(i == 14)
        utime = stof(time);
      else if(i == 15)
        stime = stof(time);
      else if(i == 16)
        cutime = stof(time);
      else if(i == 17)
        cstime = stof(time);
      else if(i == 22)
        starttime = stof(time);
      i++;
    }
  }
  float total_time = utime+stime+cutime+cstime;
  float seconds = UpTime()-starttime/sysconf(_SC_CLK_TCK);
  cpu_ = total_time/sysconf(_SC_CLK_TCK)/seconds;
  return cpu_;
}

// TODO: Return the command that generated this process
string Process::Command() {
  string command{};
  string buffer{};
  std::ifstream stream("/proc/"+to_string(pid_)+"/cmdline");
  while(stream >> buffer)
    command = command+buffer+" ";
  return command;
}

// TODO: Return this process's memory utilization
string Process::Ram() {
  string value, key;
  string line;
  std::ifstream stream("/proc/"+to_string(pid_)+"/status");
  if(stream.is_open()) {
    while(std::getline(stream, line)) {
      std::istringstream linestream(line);
      while(linestream >> key >> value) {
        if(key == "VmSize:")
          return to_string(stoi(value)/1024);
      }
    }
  }
  return "0";
}

// TODO: Return the user (name) that generated this process
string Process::User() {
  string line;
  string key, value;
  string uid_;
  string user, uid;
  std::ifstream stream("/proc/"+to_string(pid_)+"/status");
  if(stream.is_open()) {
    while(std::getline(stream, line)) {
      std::istringstream linestream(line);
      while(linestream >> key >> value) {
        if(key == "Uid:")
          uid_ = value;
      }
    }
  }
  stream.close();
  stream.open("/etc/passwd");
  if(stream.is_open()) {
    while(std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::replace(line.begin(), line.end(), 'x', ' ');
      std::istringstream linestream(line);
      while(linestream >> user >> uid) {
        if(uid == uid_)
          return user;
      }
    }
  }
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {
  string uptime;
  std::ifstream stream("/proc/"+to_string(pid_)+"/stat");
  if(stream.is_open()) {
    while(stream >> uptime)
      return stol(uptime);
  }
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const & a) const {
  return cpu_ > a.cpu_;
}