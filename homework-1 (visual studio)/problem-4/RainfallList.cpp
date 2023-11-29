#include "RainfallList.h"

RainfallList::RainfallList() {}

bool RainfallList::add(unsigned long rainfall) {
	if (rainfall <= 400 && rain_sequence.insert(rainfall) != -1)
		return true;
	return false;
}

bool RainfallList::remove(unsigned long rainfall) {
	return rain_sequence.erase(rain_sequence.find(rainfall));
}

int RainfallList::size() const {
	return rain_sequence.size();
}

unsigned long RainfallList::minimum() const {
	unsigned long min_rainfall = NO_RAINFALLS;
	unsigned long this_rainfall;
	for (int i = 0; i < rain_sequence.size(); i++) {
		rain_sequence.get(i, this_rainfall);
		if (this_rainfall < min_rainfall)
			min_rainfall = this_rainfall;
	}
	return min_rainfall;
}

unsigned long RainfallList::maximum() const {
	if (rain_sequence.empty())
		return NO_RAINFALLS;
	unsigned long max_rainfall = 0;
	unsigned long this_rainfall;
	for (int i = 0; i < rain_sequence.size(); i++) {
		rain_sequence.get(i, this_rainfall);
		if (this_rainfall > max_rainfall)
			max_rainfall = this_rainfall;
	}
	return max_rainfall;
}
