Action()
{

	web_set_sockets_option("SSL_VERSION", "2&3");

	lr_start_transaction("Registration");

		lr_start_transaction("connect_to_server");
	
			web_add_auto_header("Sec-Fetch-Site", 
				"none");
		
			web_add_auto_header("Sec-Fetch-Dest", 
				"document");
		
			web_add_auto_header("Sec-Fetch-Mode", 
				"navigate");
		
			web_add_auto_header("Sec-Fetch-User", 
				"?1");
		
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
			
			web_reg_save_param("userSession",
					"LB=<input type=\"hidden\" name=\"userSession\" value=\"",
					"RB=\"/>",
					"NotFound=ERROR",
					LAST);
		
			web_reg_find("Fail=NotFound",
			"Text= A Session ID has been created and loaded into a cookie called MSO",
			LAST);
	
			web_url("WebTours", 
				"URL=http://localhost:1080/WebTours/", 
				"TargetFrame=", 
				"Resource=0",
				"RecContentType=text/html", 
				"Referer=", 
				"Snapshot=t1.inf", 
				"Mode=HTML", 
				LAST);
	
		lr_end_transaction("connect_to_server", LR_AUTO);

		lr_start_transaction("click_sign_up");

			web_add_auto_header("Sec-Fetch-Dest", 
				"frame");
		
			web_revert_auto_header("Sec-Fetch-User");
		
			web_revert_auto_header("Upgrade-Insecure-Requests");
		
			web_add_auto_header("Sec-Fetch-Site", 
				"same-origin");
		
			lr_think_time(5);
			
			web_reg_find("Text=<B>First time registering? Please complete the form below.</B>",
				LAST);

			web_url("sign up now", 
				"URL=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/WebTours/home.html", 
				"Snapshot=t2.inf", 
				"Mode=HTML", 
				LAST);
		
		lr_end_transaction("click_sign_up",LR_AUTO);

		lr_start_transaction("click_create_acc");

			web_add_header("Origin", 
				"http://localhost:1080");
		
			web_add_auto_header("Sec-Fetch-User", 
				"?1");
		
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
		
			lr_think_time(5);
			
			web_reg_find("Text=Thank you, <b>{login}</b>",
				LAST);

			web_submit_data("login.pl", 
				"Action=http://localhost:1080/cgi-bin/login.pl", 
				"Method=POST", 
				"TargetFrame=info", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
				"Snapshot=t3.inf", 
				"Mode=HTML", 
				ITEMDATA, 
				"Name=username", "Value={login}", ENDITEM, 
				"Name=password", "Value={password}", ENDITEM, 
				"Name=passwordConfirm", "Value={password}", ENDITEM, 
				"Name=firstName", "Value={fname}", ENDITEM, 
				"Name=lastName", "Value={lname}", ENDITEM, 
				"Name=address1", "Value={street}", ENDITEM, 
				"Name=address2", "Value={city}", ENDITEM, 
				"Name=register.x", "Value=74", ENDITEM, 
				"Name=register.y", "Value=2", ENDITEM, 
				LAST);
		
		lr_end_transaction("click_create_acc",LR_AUTO);

		lr_start_transaction("click_continue");
		
			web_revert_auto_header("Sec-Fetch-User");
		
			web_revert_auto_header("Upgrade-Insecure-Requests");
		
			lr_think_time(5);
			web_reg_find("Text=Welcome, <b>{login}</b>",
				LAST);

			web_url("button_next.gif", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?page=menus", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/login.pl", 
				"Snapshot=t4.inf", 
				"Mode=HTML", 
				LAST);

		lr_end_transaction("click_continue",LR_AUTO);

		lr_start_transaction("click_sign_off");

			web_add_header("Sec-Fetch-User", 
				"?1");
		
			web_add_header("Upgrade-Insecure-Requests", 
				"1");
		
			lr_think_time(5);
			
			web_reg_find("Fail=NotFound",
						"Text= A Session ID has been created and loaded into a cookie called MSO",
						LAST);
		
			web_url("SignOff Button", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
				"Snapshot=t5.inf", 
				"Mode=HTML", 
				LAST);

		lr_end_transaction("click_sign_off",LR_AUTO);

	lr_end_transaction("Registration",LR_AUTO);

	return 0;
}