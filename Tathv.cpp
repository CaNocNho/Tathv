// dp_10.cpp
#include <iostream> //khai bao thu vien chuan c++ 
#include <thread> //khai bao thu vien thread de tao luong 
#include <chrono>	//khai bao thu vien xac dinh thoi gian(clock) 
#include <mutex>	

int myrand(int min, int max) {
  return rand()%(max-min)+min;
}

std::mutex mo;

void phil(int ph, std::mutex& ma, std::mutex& mb) {
  while(true) {
    int duration=myrand(1000, 2000);
    {
      std::lock_guard<std::mutex> g(mo);
      std::cout<<ph<<" suy nghi ve cuoc doi "<<duration<<"ms\n";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));

    std::lock_guard<std::mutex> ga(ma);
    {
      std::lock_guard<std::mutex> g(mo);
      std::cout<<"\t\t\t\t"<<ph<<" tao moi co 1 chiec thoi\n";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::lock_guard<std::mutex> gb(mb);
    {
      std::lock_guard<std::mutex> g(mo);
      std::cout<<"\n\t\t\t\t\t"<<ph<<" tao lay duoc 2 chiec dua roi :3\n";
    }

    duration=myrand(1000, 2000);
    {
      std::lock_guard<std::mutex> g(mo);
      std::cout<<"\t\t\t\t\t"<<ph<<" tao an day liu liu :3 "<<duration<<"ms\n";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
  }
}

int main() {
  std::cout<<"dp_10\n";
  srand(time(nullptr));

  std::mutex m1, m2, m3, m4, m5;

  std::thread t1([&] {phil(1, m1, m2);});
  std::thread t2([&] {phil(2, m2, m3);});
  std::thread t3([&] {phil(3, m3, m4);});
  std::thread t4([&] {phil(4, m4, m5);});
  std::thread t5([&] {phil(5, m1, m5);});

  t1.join(); //tam dung chuong trinh lai và cho ðoi thread thuc hient?m d?ng chýõng tr?nh l?i và ch? ð?i thread th?c hi?n xong. xong.
  t2.join();
  t3.join();
  t4.join();
}
