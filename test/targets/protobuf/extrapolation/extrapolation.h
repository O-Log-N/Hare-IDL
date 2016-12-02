/*******************************************************************************
Copyright (C) 2016  OLogN Technologies AG
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*******************************************************************************/

#ifndef EXTRAPOLATION_H
#define EXTRAPOLATION_H

/*
	mb: Extrapolator are supposed to work in two different scenarios.

	First, is when current value can be estimated from previous,
	in example, character is moving at constant speed, so current position
	may not need to be send if we can estimate it from previous values,
	saving some network traffic. This is done by sender before encoding.
	Receiver must be able to guess or estimate the value.

	Second, is when receiver did not get a value because of a lost packet.

	In the first use case is imporant that sender replicates the receiver
	logic. The sender has to know exactly what value the receiver will
	extrapolate, and make a decision based on that.



*/


template<class T>
class LinearExtrapolator {
private:
	const T epsilonPos;
	const T epsilonNeg;
	const size_t maxGap;

	size_t lastTick = 0;
	T lastValue = 0;
	T delta = 0;

public:
	LinearExtrapolator(T epsilonAbs, size_t maxGap)
		:epsilonPos(epsilonAbs), epsilonNeg(-epsilonAbs), maxGap(maxGap) {}

	bool getMask(size_t tick, T value) {

		size_t missingTicks = tick - lastTick;
		if (missingTicks < maxGap) {
			T extrapolated = extrapolate(tick);
			T extError = extrapolated - value;
			if( epsilonNeg < extError && extError < epsilonPos ) {
				return false;
			}
		}
		setValue(tick, value);
		return true;
	}

	T extrapolate(size_t tick) {
		size_t missingTicks = tick - lastTick;
		return lastValue + (delta * missingTicks);
	}

	void setValue(size_t tick, T value) {
		// mb: we only calculate delta with two consecutive samples
		delta = (tick == lastTick + 1) ? value - lastValue : 0;
		lastValue = value;
		lastTick = tick;
	}
};


#endif //EXTRAPOLATION_H
