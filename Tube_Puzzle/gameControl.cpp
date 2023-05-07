//GameControl.cpp
#include "gameControl.h"
#include <iostream>

TubeSet::TubeSet(int num_columns, int num_tubes)
	: m_num_columns(num_columns), m_num_tubes(num_tubes)
{
	m_array = new int* [num_columns];
	for (int i = 0; i < num_columns; i++) {
		m_array[i] = new int[num_tubes];
		for (int j = 0; j < num_tubes; j++) {
			m_array[i][j] = 0;
		}
	}
}

TubeSet::~TubeSet()
{
	for (int i = 0; i < m_num_columns; i++) {
		delete[] m_array[i];
	}
	delete[] m_array;
}

void TubeSet::fillArray(int* values)
{
	int index = 0;
	for (int i = 0; i < m_num_columns; i++) {
		for (int j = 0; j < m_num_tubes; j++) {
			m_array[i][j] = values[index];
			index++;
		}
	}
}
int TubeSet::get(int column, int tube) {
	return m_array[column][tube];
}
wxColor TubeSet::GetColor(int value) {
	wxColor color;
	switch (value) {
	case 1:
		color = wxColor(255, 0, 0); // Red
		break;
	case 2:
		color = wxColor(0, 255, 0); // Green
		break;
	case 3:
		color = wxColor(0, 0, 255); // Blue
		break;
	case 4:
		color = wxColor(255, 255, 0); // Yellow
		break;
	case 5:
		color = wxColor(255, 0, 255); // Magenta
		break;
	default:
		color = wxColor(255, 255, 255); // White
		break;
	}
	return color;
}
int TubeSet::setValue(int column, int tube, int value)
{
	int originalValue = m_array[column][tube];
	m_array[column][tube] = value;
	return originalValue;
}