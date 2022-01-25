#ifndef _FA_API_H_
    #define _FA_API_H_
     
    #define DECLDIR __declspec(dllimport)
     
    extern "C"
    {
        DECLDIR void FA_LEDWrite( unsigned char Port, unsigned char value );
        DECLDIR void FA_LEDOn( unsigned char Port, unsigned char index );
        DECLDIR void FA_LEDOff( unsigned char Port, unsigned char index );
        DECLDIR unsigned char FA_ReadSwitch( unsigned char Port, unsigned char index );
        //DECLDIR unsigned char FA_WaitSwitch( unsigned char Port, unsigned char a );
        DECLDIR void FA_SetMotors( unsigned char Port, signed int left, signed int right );
        DECLDIR unsigned int FA_ReadIR( unsigned char Port, unsigned char index );
        DECLDIR unsigned int FA_ReadLine( unsigned char Port, unsigned char index );
        DECLDIR unsigned int FA_ReadLight( unsigned char Port );
        DECLDIR void FA_Forwards(unsigned char Port, unsigned int distance);
        DECLDIR void FA_Backwards(unsigned char Port, unsigned int distance);
        DECLDIR void FA_Left(unsigned char Port, unsigned int angle);
        DECLDIR void FA_Right(unsigned char Port, unsigned int angle);
        DECLDIR void FA_SetLogoSpeed(unsigned char Port, unsigned char speed);
        DECLDIR void FA_EncoderReset(unsigned char Port);
        DECLDIR unsigned int FA_EncoderRead(unsigned char Port, unsigned char index);
        DECLDIR void FA_LCDClear(unsigned char Port);
        DECLDIR void FA_LCDPrintString(unsigned char Port, unsigned char x, unsigned char y, unsigned char * text);
        DECLDIR void FA_LCDPrintNumber(unsigned char Port, unsigned char x, unsigned char y, signed int number);
        DECLDIR void FA_LCDDrawPixel(unsigned char Port, unsigned char x, unsigned char y, unsigned char state);
        DECLDIR void FA_LCDDrawLine(unsigned char Port, unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
        DECLDIR void FA_LCDDrawRect(unsigned char Port, unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
        DECLDIR void FA_LCDBacklight(unsigned char Port, unsigned char value);
        DECLDIR void FA_LCDVerbose(unsigned char Port, unsigned char value);
		DECLDIR void FA_LCDOptions(unsigned char Port, unsigned char fg, unsigned char bg, unsigned char trans);
        DECLDIR unsigned int FA_ReadMic(unsigned char Port);
        DECLDIR void FA_PlayNote(unsigned char Port, unsigned int note, unsigned int time);
        DECLDIR unsigned char FA_GetAPIVersion(unsigned char Port);

        DECLDIR void FA_ServoEnable(unsigned char Port, unsigned char index);
        DECLDIR void FA_ServoDisable(unsigned char Port, unsigned char index);
        DECLDIR void FA_ServoSetPosition(unsigned char Port, unsigned char index, unsigned char position);
        DECLDIR void FA_ServoAutoMoveToPosition(unsigned char Port, unsigned char index, unsigned char position);
        DECLDIR void FA_ServoSetAutoMoveSpeed(unsigned char Port, unsigned char speed);

        DECLDIR unsigned char FA_CardInit( unsigned char Port );
        DECLDIR unsigned char FA_CardCreate( unsigned char Port, unsigned char * filename );
        DECLDIR unsigned char FA_CardOpen( unsigned char Port, unsigned char * filename );
        DECLDIR unsigned char FA_CardDelete( unsigned char Port, unsigned char * filename );
        DECLDIR void FA_CardWriteByte( unsigned char Port, unsigned char data );
        DECLDIR unsigned char FA_CardReadByte( unsigned char Port );
        DECLDIR unsigned char FA_CardRecordMic( unsigned char Port, unsigned char bitdepth, unsigned char samplerate, unsigned int time, unsigned char * filename);
        DECLDIR unsigned char FA_CardPlayback(unsigned char Port, unsigned char * filename);
        DECLDIR unsigned char FA_CardBitmap(unsigned char Port, unsigned char x, unsigned char y, unsigned char * filename);
            		
	    DECLDIR signed int FA_ReadAxis(unsigned char Port, unsigned char index);
	    DECLDIR unsigned int FA_ReadBearing( unsigned char Port );
  		
	    DECLDIR unsigned char FA_ComFindFirst( void );
	    DECLDIR unsigned char FA_ComQuery( unsigned char Port );
	    DECLDIR unsigned char FA_ComOpen( unsigned char Port );
	    DECLDIR unsigned char FA_ComClose( unsigned char Port );
  		
	    DECLDIR void BaudRateSet( unsigned char Port, unsigned long Baud );
	    DECLDIR unsigned int ReadCharCOM( unsigned char Port, unsigned int timeout, unsigned int timeout_val );
	    DECLDIR void SendCharCOM( unsigned char Port, unsigned char Data );
	    DECLDIR void SetDTRStatePrivate( unsigned char Port, unsigned char state );
	    DECLDIR void SetFlowControlPrivate( unsigned char Port, unsigned char state );

    }

    
 #endif
 
 