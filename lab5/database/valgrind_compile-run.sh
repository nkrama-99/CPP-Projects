g++ Main.cpp TreeDB.cpp TreeNode.cpp DBentry.cpp -std=c++11 -o database.exe
echo 
echo ***COMPILATION SUCCESSFUL
echo ***Hope you get no memoryleaks lmao
echo
valgrind --leak-check=full ./database.exe