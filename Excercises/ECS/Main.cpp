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
uint8_t RandomU8generator() 
{
	static uint8_t S = 12; 
	S ^= (S << 7);
	S ^= (S >> 5);
	S ^= (S << 3);
	return S;
}

class Entity
{
public:
	//they are in order of size for optimization
	static constexpr uint16_t NumberOfEntities = 500;
	Vec3 positionComponent[NumberOfEntities];
	Vec3 velocityComponent[NumberOfEntities];

	float jumpForce[NumberOfEntities];
	float speed[NumberOfEntities];

	int8_t health[NumberOfEntities];
	int8_t damage[NumberOfEntities];
	int8_t defense[NumberOfEntities];
	int8_t agility[NumberOfEntities];

	Item item[NumberOfEntities];

	Entity()
	{
		for (uint16_t i = 0; i < NumberOfEntities; i++)
		{
			//for now they are random just to test  but in the future no
			//positions
			positionComponent[i].X = RandomFloatgenerator();
			positionComponent[i].Y = RandomFloatgenerator();
			positionComponent[i].Z = RandomFloatgenerator();
			//velocities
			velocityComponent[i].X = RandomFloatgenerator();
			velocityComponent[i].Y = RandomFloatgenerator();
			velocityComponent[i].Z = RandomFloatgenerator();

			//stats
			jumpForce[i] = 1.2;
			speed[i] = 1.8;

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

	void AttackSystem(const uint16_t id, const uint16_t target_id)
	{
		if (is_alive(id) == false)
		{
			return;
		}
		health[target_id] -= ((damage[id] * ItemMultipliers[uint8_t(item[id])]) - defense[target_id]);

	}

	void VelocityZeroSystem(const uint16_t id)
	{
		velocityComponent[id].X = 0;
		velocityComponent[id].Y = 0;
		velocityComponent[id].Z = 0;
	}

	void VelocityUpdateSystem(const uint16_t id)
	{
		if (is_alive(id) == false)
		{
			return;
		}
		positionComponent[id].X += velocityComponent[id].X;
		positionComponent[id].Y += velocityComponent[id].Y;
		positionComponent[id].Z += velocityComponent[id].Z;
	}

	void JumpSystem(const uint16_t id)
	{	
		velocityComponent[id].Y += jumpForce[id];	
	}

	void MoveTWRSystem(const uint16_t id ,const Vec3 newPosition)
	{
		//we move on axis X and Z

		float dirX = newPosition.X - velocityComponent[id].X;
		float dirZ = newPosition.Z - velocityComponent[id].Z;

		float distance = std::sqrt(dirX * dirX + dirZ * dirZ);
		if (distance > 0.05f)
		{
			velocityComponent[id].X = (dirX / distance) * speed[id];
			velocityComponent[id].Z = (dirZ / distance) * speed[id];
		}
		else
		{
			velocityComponent[id].X = 0.0f;
			velocityComponent[id].Z = 0.0f;
		}
	}
	
	void ThinkingSystem(const uint16_t id)
	{
		//take decision like jump attack ecc ai ecc
	}

	void UpdateSystem(const uint16_t id)
	{
		ThinkingSystem(id);



		VelocityZeroSystem(id);
	}

	void UpdateAll()
	{

	}
	
};





int main()
{


}