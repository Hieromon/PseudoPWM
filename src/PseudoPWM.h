/**
 *	Pseudo PWM class implementation.
 *	@file	PseudoPWM.h
 *	@author	hieromon@gmail.com
 *	@version	1.0
 *	@date	2017-11-15
 *	@copyright	MIT license.
 */

#ifndef _PseudoPWM_H
#define _PseudoPWM_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Ticker.h>

/**
 *	Pseudo PWM class. Generate a pseudo PWM using two Tickers.
 *	This class generates a pseudo PWM by triggering PWM cycle and PWM period 
 *	with different Ticker respectively. The PWM output appears active high 
 *	on one specified port.
 */
class PseudoPWM {
public:
	/** User callback function type */
	 typedef void(*callback_t)(void);

	 /** Constructor
	  * @param	port	A port number should be output of PWM.
	  */
	 PseudoPWM(uint8_t port) : _port(port) { _cb = NULL; };

	 /** Destructor */
	~PseudoPWM() { delete &_cycleTicker; delete &_dutyTicker; };
	
	/**
	 *	Start PWM output with cycle and period previously.
	 */
	void Start() {
		pinMode(_port, OUTPUT);
		_dutyTicker.detach();
		_cycleTicker.attach_ms(Cycle, PseudoPWM::_cyclePeriod, this);
	}

	/**
	 *	Start PWM output.
	 *	@param	cycle	Milliseconds of cycle time.
	 *	@param	duty	A duty value by millisecond unit.
	 */
	void Start(uint32_t cycle, uint32_t duty) {
		Cycle = cycle;
		Duty = duty;
		Start();
	}
	
	/**
	 *	Stop PWM output.
	 */
	void Stop() {
		_cycleTicker.detach();
		_dutyTicker.detach();
	}

	/**
	 *	Attach the user callback function.
	 *	The function attached here is called every cycle period.
	 *	@param	cb	A call back function.
	 */
	void attach(callback_t cb) { _cb = cb; }

	/**
	 *	Disable the user callback function.
	 */
	void detach() { _cb = NULL; }
	
	uint32_t	Cycle;		/**< Cycle time of the PWM by millisecond unit */
	uint32_t	Duty;		/**< Duty value of the PWM cycle by millisecond unit */

private:
	static void	_cyclePeriod(PseudoPWM *t) {
		digitalWrite(t->_port, HIGH);
		t->_dutyTicker.once_ms(t->Duty, PseudoPWM::_dutyPeriod, t);
		if (t->_cb)
			t->_cb();
	}

	static void	_dutyPeriod(PseudoPWM *t) {
		digitalWrite(t->_port, LOW);
	}

	Ticker	_cycleTicker;	/**< Ticker for cycle measurement */
	Ticker	_dutyTicker;	/**< Ticker for duty measurement */
	uint8_t	_port;			/**< PWM output port */
	callback_t	_cb;		/**< Callback function */
};

#endif