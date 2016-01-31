for i in {1..100000}
do
TestGenerator/build/Debug/TestGenerator ${i} 20 | TreeTest/build/Debug/TreeTest RBTree ${i} | ErrorLogger/build/Debug/ErrorLogger ${i} e_log
echo ${i}
done
