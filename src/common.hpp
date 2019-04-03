#pragma once
#ifndef SIVOX_GAME_COMMON_HPP
#define SIVOX_GAME_COMMON_HPP

/*
 * Used to expose private or protected class members for testing.  
 *
 * Replace the 'private:' or 'protected:' keywords for parts of the code that should be exposed with
 * 'sivox_test(private):' or 'sivox_test(protected):'.
 *
 * When SIVOX_TESTING is defined, the members will be defined as public. When it is not, the members will be defined as
 * the specifier passed into the macro.
 */
#ifdef SIVOX_TESTING
#define sivox_test(spec) public
#else
#define sivox_test(spec) spec
#endif /*SIVOX_TESTING*/

#endif /*SIVOX_GAME_COMMON_HPP*/
