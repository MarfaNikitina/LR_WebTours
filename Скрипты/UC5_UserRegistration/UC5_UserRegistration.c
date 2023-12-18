UC5_UserRegistration()
{
	char *sBuff;
	int i;
	int j;
	int k;	
	
	lr_param_sprintf("username", "%s", lr_eval_string("{RandomLetter}"));

	for (i=0; i<8; i++)
		
	lr_param_sprintf("username", "%s%s", lr_eval_string("{username}"), lr_eval_string("{RandomLetter}"));
		
	lr_param_sprintf("password", "%s", lr_eval_string("{RandomLetter}"));

	for (j=0; i<6; j++)
		
	lr_param_sprintf("password", "%s%s", lr_eval_string("{password}"), lr_eval_string("{RandomLetter}"));
	
	lr_param_sprintf("lastName", "%s", lr_eval_string("{RandomLetter}"));

	for (k=0; k<6; k++)
		
	lr_param_sprintf("lastName", "%s%s", lr_eval_string("{lastName}"), lr_eval_string("{RandomLetter}"));
	
	
	lr_start_transaction("UC5_UserRegistration");
	
	lr_start_transaction("StartPage");
	
	web_reg_save_param("userSession",
	                   "LB=userSession\" value=\"",
	                   "RB=\"",
	                   LAST);
	                   
	web_reg_find("Text/IC=Web Tours",LAST);

	web_set_sockets_option("SSL_VERSION", "2&3");

	web_add_cookie("csrftoken=Pu1k109gOPWuGFN6iUUFJu41ZueeAvRA0cm8ZuPYBWoIXc2NH7hGZTrBoadTWaBz; DOMAIN=127.0.0.1");

	web_url("welcome.pl", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?signOff=true", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/WebTours/", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("StartPage",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("AddUser");
	
	web_reg_find("Text/IC=User Information",LAST);

	web_url("login.pl", 
		"URL=http://127.0.0.1:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/WebTours/home.html", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		LAST);
	lr_end_transaction("AddUser",LR_AUTO);
	
	lr_think_time(5);
	
	lr_start_transaction("UserData");
	
	web_reg_find("Text/IC=Thank you, <b>{username}</b>, for registering",LAST);
	
	web_submit_data("login.pl_2", 
		"Action=http://127.0.0.1:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=info", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value={username}", ENDITEM,
		"Name=password", "Value={password}", ENDITEM, 
		"Name=passwordConfirm", "Value={password}", ENDITEM, 
		"Name=firstName", "Value={username}", ENDITEM, 
		"Name=lastName", "Value={lastName}", ENDITEM, 
		"Name=address1", "Value={address}", ENDITEM, 
		"Name=address2", "Value={city}", ENDITEM, 
		"Name=register.x", "Value=70", ENDITEM, 
		"Name=register.y", "Value=14", ENDITEM, 
		LAST);

	lr_end_transaction("UserData", LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("SingUp");
	
	web_reg_find("Text/IC=User has returned to the home page",LAST);

	web_url("button_next.gif", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?page=menus", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/login.pl", 
		"Snapshot=t14.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("SingUp",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("Logout");
	
	web_reg_find("Text/IC=Web Tours",LAST);

	web_url("SignOff Button", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t10.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Logout",LR_AUTO);
	
	lr_end_transaction("UC5_UserRegistration", LR_AUTO);

	return 0;
}