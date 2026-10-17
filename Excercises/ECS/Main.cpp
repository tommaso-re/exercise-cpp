#include <stdint.h>
#include <iostream>

enum  class Item : const uint8_t
{
	nothing,
	fist,
	stick,
	knife,
	sword,
	axe,
};

constexpr float ItemMultipliers[] = {
	1.00f, // nothing
	1.10f, // fist
	1.20f, // stick
	1.32f, // knife
	1.45f, // sword
	1.68f  // axe
};

struct Vec3
{
	float X, Y, Z;

	Vec3()
		:X(0.0f), Y(0.0f), Z(0.0f) {};

	Vec3(float x, float y, float z)
		:X(x), Y(y), Z(z) {};
};

float RandomFloatgenerator() 
{
	static int32_t S = 12; 
	S ^= (S << 7);
	S ^= (S >> 5);
	S ^= (S << 3);
	return float(S);
}

class Entity
{
public:

	static constexpr uint16_t NumberOfEntities = 500;
	Vec3 positionComponent[NumberOfEntities];
	Vec3 velocityComponent[NumberOfEntities];
	//stats
	int8_t health[NumberOfEntities];
	int8_t damage[NumberOfEntities];
	int8_t defense[NumberOfEntities];
	int8_t agility[NumberOfEntities];


	//other things
	Item item[NumberOfEntities];

	Entity()
	{
		for (uint16_t i = 0; i < NumberOfEntities; i++)
		{
			//for now they are random just to test  but in the future no
			//positions
			positionComponent[i].X = RandomU8generator();
			positionComponent[i].Y = RandomU8generator();
			positionComponent[i].Z = RandomU8generator();
			//velocities
			velocityComponent[i].X = RandomU8generator();
			velocityComponent[i].Y = RandomU8generator();
			velocityComponent[i].Z = RandomU8generator();
			//stats
			health[i] = ((RandomU8generator() % 10) + 10);
			damage[i] = ((RandomU8generator() % 10) + 10);
			defense[i] = (RandomU8generator() % 2);
			agility[i] = (RandomU8generator() % 2);
			//things
			item[i] = Item::nothing;



		}
	}

	bool is_alive(const uint16_t id)
	{
		if ((health[id]) > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Vec3ZeroSystem(const uint16_t id)
	{
		positionComponent[id].X = 0;
		positionComponent[id].Y = 0;
		positionComponent[id].Z = 0;
	}

	void AttackSystem(const uint16_t id, const uint16_t target_id)
	{
		if (is_alive(id) == false)
		{
			return;
		}
		health[target_id] -= ((damage[id] * ItemMultipliers[uint8_t(item[id])]) - defense[target_id]);

	}

	void MoveSystem(const uint16_t id)
	{
		if (is_alive(id) == false)
		{
			return;
		}
		positionComponent[id].X += velocityComponent[id].X;
		positionComponent[id].Y += velocityComponent[id].Y;
		positionComponent[id].Z += velocityComponent[id].Z;
	}

	void MoveTWRSystem(const uint16_t id, Vec3 TargetPosition)
	{
		float DifferenceX = TargetPosition.X - positionComponent[id].X;
		float DifferenceY = TargetPosition.Y - positionComponent[id].Y;
		float DifferenceZ = TargetPosition.Z - positionComponent[id].Z;


	}

	
	void UpdateSystem()
	{
		
	}

	void UpdateAll()
	{

	}
	
};


void vec3ZeroSystem(Vec3* pos, uint16_t id)
{
	pos[id].X = 0;
	pos[id].Y = 0;
	pos[id].Z = 0;
}


int main()
{
	Entity zombies;

	
	zombies.Attack(2,3);


}