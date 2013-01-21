// inheritance_test.cpp
#include "Fightership.h"
//#include "Bombership.h"


int main()
{
	{
		Fightership fighter("F1", Vector3D(5.0f, 6.0f, -3.0f), Vector3D(1.0f, 1.0f, 0.0f), 100, 0, 10);

		fighter.draw();

		fighter.fly();
		fighter.fireLaserGun();
		fighter.fireMissile();
		fighter.fireMissile();

		fighter.draw();
	}

	system("pause");
	return 0;
}

// From p. 26 in slides, as an illustration. You should use SmartPointers!
/*int main()
{
	Bombership* p_bombership = new Bombership;
    Spaceship* p_spaceship = p_bombership;
    Spaceship* p_spaceship2 = new Bombership();
    Bombership* p_bombership2 = reinterpret_cast<Bombership*>(new Spaceship);

    std::cout << "\n- Deleting bombershipPtr: (to Bombership object) -" << std::endl;
    delete p_bombership;
    std::cout << "- Deleting spaceshipPtr2: (to Bombership object) -" << std::endl;
    delete p_spaceship2;
    std::cout << "- Deleting bombershipPtr2: (to spaceship object) -" << std::endl;
    delete p_bombership2;
    std::cout << "- End deletes. -" << std::endl << std::endl;

    system("pause");
    return 0;
}*/