#pragma once
#ifndef _PARALLAX_KEYS_H_
#define _PARALLAX_KEYS_H_

#ifdef PARALLAX_API_OPENGL

#include "ext/GLFW/glfw3.h"

// Key states
#define PARALLAX_RELEASE				GLFW_RELEASE
#define PARALLAX_PRESS					GLFW_PRESS
#define PARALLAX_REPEAT					GLFW_REPEAT

// Printable keys
#define PARALLAX_KEY_SPACE				GLFW_KEY_SPACE        
#define PARALLAX_KEY_APOSTROPHE   		GLFW_KEY_APOSTROPHE   
#define PARALLAX_KEY_COMMA        		GLFW_KEY_COMMA        
#define PARALLAX_KEY_MINUS        		GLFW_KEY_MINUS        
#define PARALLAX_KEY_PERIOD       		GLFW_KEY_PERIOD       
#define PARALLAX_KEY_SLASH        		GLFW_KEY_SLASH        
#define PARALLAX_KEY_0            		GLFW_KEY_0            
#define PARALLAX_KEY_1            		GLFW_KEY_1            
#define PARALLAX_KEY_2            		GLFW_KEY_2            
#define PARALLAX_KEY_3            		GLFW_KEY_3            
#define PARALLAX_KEY_4            		GLFW_KEY_4            
#define PARALLAX_KEY_5            		GLFW_KEY_5            
#define PARALLAX_KEY_6            		GLFW_KEY_6            
#define PARALLAX_KEY_7            		GLFW_KEY_7            
#define PARALLAX_KEY_8            		GLFW_KEY_8            
#define PARALLAX_KEY_9            		GLFW_KEY_9            
#define PARALLAX_KEY_SEMICOLON    		GLFW_KEY_SEMICOLON    
#define PARALLAX_KEY_EQUAL        		GLFW_KEY_EQUAL        
#define PARALLAX_KEY_A            		GLFW_KEY_A            
#define PARALLAX_KEY_B            		GLFW_KEY_B            
#define PARALLAX_KEY_C            		GLFW_KEY_C            
#define PARALLAX_KEY_D            		GLFW_KEY_D            
#define PARALLAX_KEY_E            		GLFW_KEY_E            
#define PARALLAX_KEY_F            		GLFW_KEY_F            
#define PARALLAX_KEY_G            		GLFW_KEY_G            
#define PARALLAX_KEY_H            		GLFW_KEY_H            
#define PARALLAX_KEY_I            		GLFW_KEY_I            
#define PARALLAX_KEY_J            		GLFW_KEY_J            
#define PARALLAX_KEY_K            		GLFW_KEY_K            
#define PARALLAX_KEY_L            		GLFW_KEY_L            
#define PARALLAX_KEY_M            		GLFW_KEY_M            
#define PARALLAX_KEY_N            		GLFW_KEY_N            
#define PARALLAX_KEY_O            		GLFW_KEY_O            
#define PARALLAX_KEY_P            		GLFW_KEY_P            
#define PARALLAX_KEY_Q            		GLFW_KEY_Q            
#define PARALLAX_KEY_R            		GLFW_KEY_R            
#define PARALLAX_KEY_S            		GLFW_KEY_S            
#define PARALLAX_KEY_T            		GLFW_KEY_T            
#define PARALLAX_KEY_U            		GLFW_KEY_U            
#define PARALLAX_KEY_V            		GLFW_KEY_V            
#define PARALLAX_KEY_W            		GLFW_KEY_W            
#define PARALLAX_KEY_X            		GLFW_KEY_X            
#define PARALLAX_KEY_Y            		GLFW_KEY_Y            
#define PARALLAX_KEY_Z            		GLFW_KEY_Z            
#define PARALLAX_KEY_LEFT_BRACKET 		GLFW_KEY_LEFT_BRACKET 
#define PARALLAX_KEY_BACKSLASH    		GLFW_KEY_BACKSLASH    
#define PARALLAX_KEY_RIGHT_BRACKET		GLFW_KEY_RIGHT_BRACKET
#define PARALLAX_KEY_GRAVE_ACCENT 		GLFW_KEY_GRAVE_ACCENT 
#define PARALLAX_KEY_WORLD_1      		GLFW_KEY_WORLD_1      
#define PARALLAX_KEY_WORLD_2      		GLFW_KEY_WORLD_2      

// Functional keys
#define PARALLAX_KEY_ESCAPE				GLFW_KEY_ESCAPE          
#define PARALLAX_KEY_ENTER          	GLFW_KEY_ENTER           
#define PARALLAX_KEY_TAB            	GLFW_KEY_TAB             
#define PARALLAX_KEY_BACKSPACE      	GLFW_KEY_BACKSPACE       
#define PARALLAX_KEY_INSERT         	GLFW_KEY_INSERT          
#define PARALLAX_KEY_DELETE         	GLFW_KEY_DELETE          
#define PARALLAX_KEY_RIGHT          	GLFW_KEY_RIGHT           
#define PARALLAX_KEY_LEFT           	GLFW_KEY_LEFT            
#define PARALLAX_KEY_DOWN           	GLFW_KEY_DOWN            
#define PARALLAX_KEY_UP             	GLFW_KEY_UP              
#define PARALLAX_KEY_PAGE_UP        	GLFW_KEY_PAGE_UP         
#define PARALLAX_KEY_PAGE_DOWN      	GLFW_KEY_PAGE_DOWN       
#define PARALLAX_KEY_HOME           	GLFW_KEY_HOME            
#define PARALLAX_KEY_END            	GLFW_KEY_END             
#define PARALLAX_KEY_CAPS_LOCK      	GLFW_KEY_CAPS_LOCK       
#define PARALLAX_KEY_SCROLL_LOCK    	GLFW_KEY_SCROLL_LOCK     
#define PARALLAX_KEY_NUM_LOCK       	GLFW_KEY_NUM_LOCK        
#define PARALLAX_KEY_PRINT_SCREEN   	GLFW_KEY_PRINT_SCREEN    
#define PARALLAX_KEY_PAUSE          	GLFW_KEY_PAUSE           
#define PARALLAX_KEY_F1             	GLFW_KEY_F1              
#define PARALLAX_KEY_F2             	GLFW_KEY_F2              
#define PARALLAX_KEY_F3             	GLFW_KEY_F3              
#define PARALLAX_KEY_F4             	GLFW_KEY_F4              
#define PARALLAX_KEY_F5             	GLFW_KEY_F5              
#define PARALLAX_KEY_F6             	GLFW_KEY_F6              
#define PARALLAX_KEY_F7             	GLFW_KEY_F7              
#define PARALLAX_KEY_F8             	GLFW_KEY_F8              
#define PARALLAX_KEY_F9             	GLFW_KEY_F9              
#define PARALLAX_KEY_F10            	GLFW_KEY_F10             
#define PARALLAX_KEY_F11            	GLFW_KEY_F11             
#define PARALLAX_KEY_F12            	GLFW_KEY_F12             
#define PARALLAX_KEY_F13            	GLFW_KEY_F13             
#define PARALLAX_KEY_F14            	GLFW_KEY_F14             
#define PARALLAX_KEY_F15            	GLFW_KEY_F15             
#define PARALLAX_KEY_F16            	GLFW_KEY_F16             
#define PARALLAX_KEY_F17            	GLFW_KEY_F17             
#define PARALLAX_KEY_F18            	GLFW_KEY_F18             
#define PARALLAX_KEY_F19            	GLFW_KEY_F19             
#define PARALLAX_KEY_F20            	GLFW_KEY_F20             
#define PARALLAX_KEY_F21            	GLFW_KEY_F21             
#define PARALLAX_KEY_F22            	GLFW_KEY_F22             
#define PARALLAX_KEY_F23            	GLFW_KEY_F23             
#define PARALLAX_KEY_F24            	GLFW_KEY_F24             
#define PARALLAX_KEY_F25            	GLFW_KEY_F25             
#define PARALLAX_KEY_KP_0           	GLFW_KEY_KP_0            
#define PARALLAX_KEY_KP_1           	GLFW_KEY_KP_1            
#define PARALLAX_KEY_KP_2           	GLFW_KEY_KP_2            
#define PARALLAX_KEY_KP_3           	GLFW_KEY_KP_3            
#define PARALLAX_KEY_KP_4           	GLFW_KEY_KP_4            
#define PARALLAX_KEY_KP_5           	GLFW_KEY_KP_5            
#define PARALLAX_KEY_KP_6           	GLFW_KEY_KP_6            
#define PARALLAX_KEY_KP_7           	GLFW_KEY_KP_7            
#define PARALLAX_KEY_KP_8           	GLFW_KEY_KP_8            
#define PARALLAX_KEY_KP_9           	GLFW_KEY_KP_9            
#define PARALLAX_KEY_KP_DECIMAL     	GLFW_KEY_KP_DECIMAL      
#define PARALLAX_KEY_KP_DIVIDE      	GLFW_KEY_KP_DIVIDE       
#define PARALLAX_KEY_KP_MULTIPLY    	GLFW_KEY_KP_MULTIPLY     
#define PARALLAX_KEY_KP_SUBTRACT    	GLFW_KEY_KP_SUBTRACT     
#define PARALLAX_KEY_KP_ADD         	GLFW_KEY_KP_ADD          
#define PARALLAX_KEY_KP_ENTER       	GLFW_KEY_KP_ENTER        
#define PARALLAX_KEY_KP_EQUAL       	GLFW_KEY_KP_EQUAL        
#define PARALLAX_KEY_LEFT_SHIFT     	GLFW_KEY_LEFT_SHIFT      
#define PARALLAX_KEY_LEFT_CONTROL   	GLFW_KEY_LEFT_CONTROL    
#define PARALLAX_KEY_LEFT_ALT       	GLFW_KEY_LEFT_ALT        
#define PARALLAX_KEY_LEFT_SUPER     	GLFW_KEY_LEFT_SUPER      
#define PARALLAX_KEY_RIGHT_SHIFT    	GLFW_KEY_RIGHT_SHIFT     
#define PARALLAX_KEY_RIGHT_CONTROL  	GLFW_KEY_RIGHT_CONTROL   
#define PARALLAX_KEY_RIGHT_ALT      	GLFW_KEY_RIGHT_ALT       
#define PARALLAX_KEY_RIGHT_SUPER    	GLFW_KEY_RIGHT_SUPER     
#define PARALLAX_KEY_MENU           	GLFW_KEY_MENU       

// Modifiers
// If this bit is set one or more Shift keys were held down.
#define PARALLAX_MOD_SHIFT				GLFW_MOD_SHIFT

//If this bit is set one or more Control keys were held down.
#define PARALLAX_MOD_CONTROL			GLFW_MOD_CONTROL

// If this bit is set one or more Alt keys were held down.
#define PARALLAX_MOD_ALT				GLFW_MOD_ALT

// If this bit is set one or more Super keys were held down.
#define PARALLAX_MOD_SUPER				GLFW_MOD_SUPER


// Mouse buttons
#define PARALLAX_MOUSE_BUTTON_1        GLFW_MOUSE_BUTTON_1     
#define PARALLAX_MOUSE_BUTTON_2        GLFW_MOUSE_BUTTON_2     
#define PARALLAX_MOUSE_BUTTON_3        GLFW_MOUSE_BUTTON_3     
#define PARALLAX_MOUSE_BUTTON_4        GLFW_MOUSE_BUTTON_4     
#define PARALLAX_MOUSE_BUTTON_5        GLFW_MOUSE_BUTTON_5     
#define PARALLAX_MOUSE_BUTTON_6        GLFW_MOUSE_BUTTON_6     
#define PARALLAX_MOUSE_BUTTON_7        GLFW_MOUSE_BUTTON_7     
#define PARALLAX_MOUSE_BUTTON_8        GLFW_MOUSE_BUTTON_8     
#define PARALLAX_MOUSE_BUTTON_LAST     GLFW_MOUSE_BUTTON_LAST  
#define PARALLAX_MOUSE_BUTTON_LEFT     GLFW_MOUSE_BUTTON_LEFT  
#define PARALLAX_MOUSE_BUTTON_RIGHT    GLFW_MOUSE_BUTTON_RIGHT 
#define PARALLAX_MOUSE_BUTTON_MIDDLE   GLFW_MOUSE_BUTTON_MIDDLE

#endif
#endif
