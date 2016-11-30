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


/*
	mb: Estimators are supposed to work in two different scenarios.

	First, is when current value can be estimated from previous,
	in example, character is moving at constant speed, so current position
	may not need to be send if we can estimate it from previous values,
	saving some network traffic. This is done by sender before encoding.
	Receiver must be able to guess or estimate the value.

	Second, is when receiver did not get a value because of a lost packet.
*/

class LinearEstimatorDouble {
private:
	const double epsilonPos;
	const double epsilonNeg;

	size_t lastTick = 0;
	double lastValue = 0;
	double delta = 0;

public:
	DoubleState(double epsilonAbs) :epsilongPos(epsilonAbs), epsilonNeg(-epsilonAbs) {}

	bool needValue(size_t tick, double value) {

		double estimated = estimateInternal(tick);
		double estError = estimated - value;
		if( epsilonNeg < estError && estError < epsilonPos ) {
			lastValue = estimated;
			lastTick = tick;
			return false;
		}
		else {
			setValue(tick, value);
			return true;
		}
	}

	double estimate(size_t tick) {
		lastValue = estimateInternal(tick);
		lastTick = tick;
		return lastValue;
	}

	void setValue(size_t tick, double value) {
		delta = (tick == lastTick + 1) ? value - lastValue : 0;
		lastValue = value;
		lastTick = tick;
	}

private:
	double estimateInternal(size_t tick) {
		size_t missingTicks = tick - lastTick;
		return lastValue + (delta * missingTicks);
	}


};
