/*
    外观模式Facade：为子系统中的一组接口提供一个一致的界面，此模式定义了一个高层接口，这个接口使得这一子系统更加容易使用。
    外观类直到哪些子系统负责处理请求，将客户的请求代理给适当的子系统对象
    子系统类集合中的每个子系统类实现其功能，处理外观类对象指派的任务，没有对上一层对象的引用。
    简化接口：通过提供一个简单的接口，隐藏了子系统的复杂性。
    松耦合：客户端代码与子系统之间的耦合度降低，使得代码更容易维护和扩展。
    更好的封装性：将子系统的具体实现细节封装在外观类中，增强了代码的可读性和可维护性。
*/ 

#include <iostream>

// 子系统1：DVD 播放器
class DVDPlayer {
public:
    void on() {
        std::cout << "DVD Player is ON" << std::endl;
    }

    void play(const std::string& movie) {
        std::cout << "Playing movie: " << movie << std::endl;
    }

    void off() {
        std::cout << "DVD Player is OFF" << std::endl;
    }
};

// 子系统2：音响系统
class SoundSystem {
public:
    void on() {
        std::cout << "Sound System is ON" << std::endl;
    }

    void setVolume(int volume) {
        std::cout << "Setting volume to: " << volume << std::endl;
    }

    void off() {
        std::cout << "Sound System is OFF" << std::endl;
    }
};

// 子系统3：投影仪
class Projector {
public:
    void on() {
        std::cout << "Projector is ON" << std::endl;
    }

    void setInput(const std::string& input) {
        std::cout << "Setting projector input to: " << input << std::endl;
    }

    void off() {
        std::cout << "Projector is OFF" << std::endl;
    }
};

// 外观类：家庭影院，封装了调用子系统的方法，提供简单的接口，由该类负责调用子系统的接口
class HomeTheaterFacade {
private:
    DVDPlayer* dvdPlayer;
    SoundSystem* soundSystem;
    Projector* projector;

public:
    HomeTheaterFacade() {
        dvdPlayer = new DVDPlayer();
        soundSystem = new SoundSystem();
        projector = new Projector();
    }
    HomeTheaterFacade(DVDPlayer* dvd, SoundSystem* sound, Projector* proj)
        : dvdPlayer(dvd), soundSystem(sound), projector(proj) {}

    void watchMovie(const std::string& movie) {
        std::cout << "Get ready to watch a movie..." << std::endl;
        projector->on();
        projector->setInput("DVD");
        soundSystem->on();
        soundSystem->setVolume(10);
        dvdPlayer->on();
        dvdPlayer->play(movie);
    }

    void endMovie() {
        std::cout << "Shutting down movie theater..." << std::endl;
        dvdPlayer->off();
        soundSystem->off();
        projector->off();
    }
};

// 客户端代码
int main() {
    // DVDPlayer dvdPlayer;
    // SoundSystem soundSystem;
    // Projector projector;

    // HomeTheaterFacade homeTheater(&dvdPlayer, &soundSystem, &projector);

    HomeTheaterFacade homeTheater;

    homeTheater.watchMovie("Inception");
    std::cout << "Movie is playing..." << std::endl;
    homeTheater.endMovie();

    return 0;
}
