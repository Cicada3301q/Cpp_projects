/// =========================================================================
/// based off of code written by pfederl@ucalgary.ca in 2020, for CPSC457.
/// =========================================================================
/// Author: Quenten Welch
///
/// You can delete all contents of this file and start from scratch if
/// you wish, but you need to implement the getDirStats() function as
/// defined in "getDirStats.h".

#include "getDirStats.h"
#include "digester.h"
#include <unordered_map>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <set>
#include <algorithm>
#include <cstdio>

static bool
is_dir( const std::string & path)
{
  struct stat buff;
  if( 0 != stat( path.c_str(), & buff))
    return false;
  return S_ISDIR(buff.st_mode);
}

// ======================================================================
// You need to re-implement this function !!!!
// ======================================================================
//
// getDirStats() computes stats about directory dir_name
// if successful, it return true and stores the results in 'res'
// on failure, it returns false, and res is in undefined state
//

std::string file_type(const std::string dir_name)
{
	std::string ftype;
    // I like C++ strings better than C strings, they waste more memory
    std::string fname = dir_name;
    // prepare the command to execute in popen()
    std::string cmd = "file -b " + fname;
    // run the command in popen()
    FILE * fp = popen( cmd.c_str(), "r");
    if( fp == nullptr) {
      printf("popen() failed, quitting\n");
      exit(-1);
}

    // get the output of popen() using fgets(3) into raw C-style char buffer
    //removed ftype from here
    char buff[1026];
    char * res = fgets(buff, sizeof(buff), fp);
    // try to parse the buffer
    if( res != nullptr) {
      // find the end of the first field ('\0', or '\n' or ',')
      int eol = 0;
      while(buff[eol] != ',' && buff[eol] != '\n' && buff[eol] != 0) eol ++;
      // terminate the string
      buff[eol] = 0;
      // remember the type
      ftype = buff;
    } else {
      // file(1) did not produce any output... no idea why, so let's
      // just skip the file, but make the file type something bizare
      ftype = "file(1) failed, not sure why";
    }


 
 return ftype;
}







bool
getDirStats(const std::string & dir_name, Results & res)
{
  // The results below are all hard-coded, to show you all the fields
  // you need to calculate. You should delete all code below and
  // replace it with your own code.
//variables:
//holds value of largest file size
res.largest_file_size = 0;
//total number of directories in the directory
res.n_dirs = -1;
//total number of files in the directory
res.n_files = 0;
//size of all files
res.all_files_size = 0;
//Unordered map containing [file_type] [number of that file type found]
std::unordered_map<std::string,int> file_map;
std::unordered_map<std::string,std::vector<std::string>> dup_map;


  if( ! is_dir(dir_name))
    return false;

  std::vector<std::string> stack;
  stack.push_back(dir_name);
  while( ! stack.empty()) {
    auto dirname = stack.back();
    stack.pop_back();



    DIR * dir = opendir( dirname.c_str());
    if(!dir){
	struct stat stats;
	stat(dirname.c_str(), &stats);
	res.all_files_size += stats.st_size;
	res.n_files += 1;
	auto f = file_type(dirname);
	file_map[f] +=1;
	auto hash = sha256_from_file(dirname);
	dup_map [hash].push_back(dirname.c_str());

	if(stats.st_size > res.largest_file_size){
		res.largest_file_size = stats.st_size;
		res.largest_file_path = dirname.c_str();
	}
	
	}
    if( dir) {
	res.n_dirs += 1;
      while(1) {

	dirent * de = readdir( dir);
	if( ! de) break;
	std::string name = de-> d_name;
	if( name == "." || name == "..") continue;
	std::string path = dirname + "/" + de-> d_name;
	stack.push_back( path);
      }
      closedir( dir);
    }
  }

std::vector<std::pair<int,std::string>> arr;
  for(auto & h : file_map){
	arr.emplace_back(-h.second, h.first);
}
 if(arr.size() > 5) {
	std::partial_sort(arr.begin(), arr.begin() + 5, arr.end());
	arr.resize(5);
} else{
	std::sort(arr.begin(), arr.end());
}
//std::vector<std::string> most_common;
for(auto & a : arr){
	res.most_common_types.push_back(a.second.c_str());
}
std::vector<std::pair<int,std::string>> dup_arr;
for (auto & d : dup_map){
	dup_arr.emplace_back(-d.second.size(), d.first);
}
if(dup_arr.size() > 5) {
	std::partial_sort(dup_arr.begin(), dup_arr.begin() + 5, dup_arr.end());
	dup_arr.resize(5);
} else{
	std::sort(dup_arr.begin(), dup_arr.end());
}

for (auto & b : dup_arr){
	if(dup_map[b.second.c_str()].size() > 1)
	res.duplicate_files.push_back(dup_map[b.second.c_str()]);
}

  return true;
}
