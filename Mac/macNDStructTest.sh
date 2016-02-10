for i in {1..100000}
do
TestGenerator/build/Debug/TestGenerator ${i} 20 | NDStructTest/build/Debug/NDStructTest treap ${i} | ErrorLogger/build/Debug/ErrorLogger ${i} e_log
echo ${i}
done
