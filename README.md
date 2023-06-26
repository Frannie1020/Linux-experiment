# Linux experiment_(Statistical analysis software for documents based on a plug-in framework structure)
[![Author](https://img.shields.io/badge/Author-Frannie1020-blue.svg "Author")](https://Frannie1020.github.io "Author")
[![Build Status](https://travis-ci.com/JoeyBling/yilia-plus-demo.svg?branch=master)](https://travis-ci.com/JoeyBling/yilia-plus-demo)


## Table of Contents

- [Assignment requirements](#assignmentrequirements)
- [Design and implementation](#designandimplementation)
- [Test pictures](#Testpictures)



## Assignment requirements  
1: Implement a number of document statistical analysis functions in the form of plug-ins. The functions to be implemented include at least  
(1) Counting the number of lines in a given file  
(2) Counting the number of words in a given file  
(3) Counting the number of lines in a given directory for all files with a given suffix. For example, the number of lines of all .c files in the /root directory. Note that a recursive traversal of the specified directory is required.  

2: The files being counted use ASCII encoding. Each of the above functions is implemented using a separate plugin. The plug-in framework program needs to be in a loop, constantly receiving commands from the user. It is not possible to use command line arguments to specify the plug-in function to be executed and its parameters.  

3: Plus: whenever a plugin run command is received, the plugin framework program can create a new process and let that process go to run the plugin. More plug-ins are implemented.  

## Design and implementation  
1: The assignment requires three elements, I refer to the wc command in linux, and then implement an additional function that is to count the file size, and for the specified directory and non-specified directory each implement three functions. So a total of 6 plugins have been implemented. (Extra credit 1) where (4) (5) (6) are additional implemented functions.  
(1) Counting the number of lines in a given file  
(2) Counting the number of lines of all files in a given directory with a given suffix  
(3) Counting the number of words in a given file  
(4) Counts the number of words in a given directory for all files with a given suffix  
(5) Counting the size of a given file  
(6) Counting the size of all files in the specified directory with the specified suffix  

## Test pictures (only a small part of pictures are shown, since the pictures are numerous.)

![image](https://github.com/Frannie1020/Linux-experiment/assets/137517674/5bf4b4a5-86fa-4a07-afe1-96defc29ad8b)


![image](https://github.com/Frannie1020/Linux-experiment/assets/137517674/cf1dd466-a193-4b68-ba77-aac0edaf76fd)


![image](https://github.com/Frannie1020/Linux-experiment/assets/137517674/792ad1d2-0927-4872-95f3-b37dd4b4e8fe)


![image](https://github.com/Frannie1020/Linux-experiment/assets/137517674/25146629-0777-4d77-ae0b-5858c2de368c)  

![image](https://github.com/Frannie1020/Linux-experiment/assets/137517674/c9e049d9-6b60-483d-a384-1bb96409fc38)  

![image](https://github.com/Frannie1020/Linux-experiment/assets/137517674/5e610a72-4554-403c-a691-23c7e70089d3)  

![image](https://github.com/Frannie1020/Linux-experiment/assets/137517674/e9a8aa6c-8a69-41a4-99a3-5c86286d92bb)  

![image](https://github.com/Frannie1020/Linux-experiment/assets/137517674/f4cfd93e-5f86-42b5-97c1-46da83574335)

