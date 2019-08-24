 //-------------------------------------------------------------------------------------
// Name:		dudelib
// Description:	An avrdude compatible library
// Use this library to program target arduino boards through a "master" arduino
//
// History:    
//	16/12/2014 - Initial release on GitHub
//
// License
// "MIT Open Source Software License":
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//-------------------------------------------------------------------------------------
#ifndef DUDELIB_H
#define DUDELIB_H

//Target section: this is for Avr328p
#define TARGET_PAGESIZE  	  128
#define MAX_BUFFER          16

extern "C" {
	// callback function types
    typedef void (*resetCallback)();
} 

// Dude
class DudeLib {
private:
    //load flash memory address
    uint8_t load_address(uint16_t address);
    //Write flash page
    uint8_t write_page(uint8_t* buffer, uint16_t length);
    //Read flash page
    uint8_t read_page(uint8_t* buffer, uint16_t length);
    //Leave program mode (restart target device)
    uint8_t leave_program_mode();
    //Send stk500 command to target device
    void send(uint16_t length);
    void send(uint8_t* buffer, uint16_t length);
    //Check empty response from target device
    uint8_t empty_response();
    //Check response with data from target device
    uint8_t response(uint8_t* buffer, uint8_t length, uint8_t start);
    //Receive data before timeout
    uint8_t receive();
	//convert ascii char to nibble value
    char char_to_hex(char a);

    HardwareSerial* _serial;
    uint8_t _tx_buf[MAX_BUFFER];
    uint8_t _page_buffer[TARGET_PAGESIZE];
    uint8_t _temp_buffer[TARGET_PAGESIZE];
    uint8_t _tx_enable;
    uint8_t _cs;
    uint8_t _error;

public:
    uint8_t begin(HardwareSerial *serial, uint8_t tx_enable_pin, uint8_t cs_pin);

    //Check device connection
    uint8_t sync();

    //Get target device information
    uint8_t get_information(uint8_t* info);

    //program target arduino with hex file and optionally verify programmed firmware
    uint16_t program(char *filename);
    uint8_t verify(char *filename);

    // //read firmware from target arduino and write to out_file
    // uint8_t read(char *out_filename);

    //reset callback;
    resetCallback reset_device;

    //error status
    inline uint8_t get_error() { return _error; }
};

#endif

