# Student:Syfur Rahman
# Test on lab computer
## Issue Explanation and Resolution 
## Summary
# When running the make command in the computer lab, there are two warnings related to the test_points2d.cc file. Despite these warnings, the #program runs correctly and produces the expected output when executed with ./test_points2d < test_input_file.txt.

# Details
# The specific warnings are related to unqualified calls to std::move. These warnings occur because the move function is used without explicitly qualifying it with the std:: namespace.
# Despite these warnings, the program compiles and runs correctly. When executing ./test_points2d < test_input_file.txt, it produces the correct output.
