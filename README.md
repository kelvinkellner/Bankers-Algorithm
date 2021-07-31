_<h1 align= "center">Bankers-Algorithm</h1>_

<h4 align= "center">CP386 Assignment 4</h4>

# Description

What is Bankers-Algorithm? (a Brief description of it)

# Installation

--> C Programming Language<br/>
--> GCC Complier for C<br/>
--> Windows Subsystem for Linux<br/>

Compile the program using GCC. When running, pass a list of space-delimited integers as arguments.
The value of the number represents the number of available resources of that type of resource.
Edit sample4_in.txt to change the customers. Each line in the file represents a thread,
and the comma-delimited values represent the amount of each type of resource that the thread needs.

To compile and run:<br/>
<img src="./img/ss_1.png" alt="screenshot of compiling and running the program" /><br/>

# Features / Commands

- Request resources:<br/>
  Requests an allocation of resources to a thread/customer, succeeds if resources are currently available and system remains safe after processing request, fails otherwise.<br/>
  <img src="./img/ss_2.png" alt="screenshot of requesting resources successfully" /><br/>
  <img src="./img/ss_3.png" alt="screenshot of request for resources failing" /><br/>
  <br/>
- Release resources:<br/>
  Releases resources currently being used by a thread/customer and makes them available again, fails if thread has not been allocated those resources.<br/>
  <img src="./img/ss_4.png" alt="screenshot of releasing resources successfully" /><br/>
  <img src="./img/ss_5.png" alt="screenshot of request to release resources failing" /><br/>
  <br/>
- Status:<br/>
  Displays the status of the system including available resources, and maximum, allocated, and needed resources for each thread/customer.<br/>
  <img src="./img/ss_6.png" alt="screenshot of displaying status of the system" /><br/>
  <br/>
- Run:<br/>
  Determines if there is a safe sequence for the threads/customers and executes the sequence if possible.<br/>
  <img src="./img/ss_7.png" alt="screenshot of running the processes" /><br/>
  <br/>
- Exit:<br/>
  Terminates the program.<br/>
  <img src="./img/ss_8.png" alt="screenshot of exiting the program" /><br/>
  <br/>

# Individual Contribution

### _Function-Wise_

| Function                | Kelvin  | Nish  |
| ----------------------- | ------  | ----- |
| main                    |    X    |       |
| run_program             |    X    |   X   |
| load_available_resoures |         |   X   |
| load_customer_resources |    X    |   X   |
| display_status          |    X    |       |
| request_resources       |    X    |   X   |
| release_resources       |    X    |   X   |
| run_resources           |    X    |   X   |
| is_safe                 |    X    |   X   |
| handle_request          |    X    |   X   |

# Test cases

See an example test case [here](https://github.com/kelvinkellner/Bankers-Algorithm/blob/main/docs/sample_output.md).

# Contributors

--> [Kelvin Kellner](https://github.com/kelvinkellner)<br/>
--> [Nishant Tewari](https://github.com/XSilviaX)<br/>

# Credits

--> [GeeksforGeeks - Banker’s Algorithm in Operating System](https://www.geeksforgeeks.org/bankers-algorithm-in-operating-system-2/)<br/>

# Project License

This project is licensed under the **MIT License** which is located [here](https://github.com/kelvinkellner/Bankers-Algorithm/blob/51cdac26b261e5d1328c41437b065f31d17f4da9/LICENSE).
