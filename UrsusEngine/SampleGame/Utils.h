#pragma once

enum RotateDirection
{
	RotateDirectionLeft,
	RotateDirectionRight,
	RotateDirectionNone
};

const unsigned char EnemyCollisionFlag = 1 << 0;
const unsigned char BulletCollisionFlag = 1 << 1;
const unsigned char ItemCollisionFlag = 1 << 2;