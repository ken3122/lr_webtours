Action()
{

	web_set_sockets_option("SSL_VERSION", "2&3");
	
	lr_start_transaction("01_FindFlight");
	
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
	
		lr_start_transaction("login");
	
			web_revert_auto_header("Sec-Fetch-User");
		
			web_add_auto_header("Sec-Fetch-Dest", 
				"frame");
		
			web_revert_auto_header("Upgrade-Insecure-Requests");
		
			web_add_header("Origin", 
				"http://localhost:1080");
		
			web_add_auto_header("Sec-Fetch-Site", 
				"same-origin");
		
			lr_think_time(5);
			
			web_reg_find("Fail=NotFound",
						"Text=User password was correct",
						LAST);
			
			web_reg_find("Fail=NotFound",
			             "Text=Welcome, <b>{login}</b>",
						LAST);
	
			web_submit_data("login.pl", 
				"Action=http://localhost:1080/cgi-bin/login.pl", 
				"Method=POST", 
				"TargetFrame=body", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home", 
				"Snapshot=t2.inf", 
				"Mode=HTML", 
				ITEMDATA, 
				"Name=userSession", "Value={userSession}", ENDITEM, 
				"Name=username", "Value={login}", ENDITEM, 
				"Name=password", "Value={password}", ENDITEM, 
				"Name=login.x", "Value=82", ENDITEM, 
				"Name=login.y", "Value=6", ENDITEM, 
				"Name=JSFormSubmit", "Value=off", ENDITEM, 
				LAST);
		
		lr_end_transaction("login",LR_AUTO);
	
		lr_start_transaction("click_flights");
	
			web_add_auto_header("Sec-Fetch-User", 
				"?1");
		
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
		
			lr_think_time(5);
			
			web_reg_find("Fail=NotFound",
						"Text=</td></tr> <tr><td align=\"left\">Arrival City :</td> <td><select name=\"arrive\" >",
						LAST);
			
			web_url("Search Flights Button", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
				"Snapshot=t3.inf", 
				"Mode=HTML", 
				LAST);
	
		lr_end_transaction("click_flights",LR_AUTO);
	
		lr_start_transaction("click_find_flight");
	
			web_add_header("Origin", 
				"http://localhost:1080");
		
			lr_think_time(5);
			
			web_reg_find("Fail=NotFound",
			             "Text=blockquote>Flight departing from <B>{depart}</B> to <B>{arrive}</B> on <B>{departDate}</B>",
						LAST);
			
			web_submit_data("reservations.pl", 
				"Action=http://localhost:1080/cgi-bin/reservations.pl", 
				"Method=POST", 
				"TargetFrame=", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
				"Snapshot=t4.inf", 
				"Mode=HTML", 
				ITEMDATA, 
				"Name=advanceDiscount", "Value=0", ENDITEM, 
				"Name=depart", "Value={depart}", ENDITEM, 
				"Name=departDate", "Value={departDate}", ENDITEM, 
				"Name=arrive", "Value={arrive}", ENDITEM, 
				"Name=returnDate", "Value={returnDate}", ENDITEM, 
				"Name=numPassengers", "Value=1", ENDITEM, 
				"Name=seatPref", "Value={seatPref}", ENDITEM, 
				"Name=seatType", "Value={seatType}", ENDITEM, 
				"Name=findFlights.x", "Value=42", ENDITEM, 
				"Name=findFlights.y", "Value=13", ENDITEM, 
				"Name=.cgifields", "Value=roundtrip", ENDITEM, 
				"Name=.cgifields", "Value=seatType", ENDITEM, 
				"Name=.cgifields", "Value=seatPref", ENDITEM, 
				LAST);
	
		lr_end_transaction("click_find_flight",LR_AUTO);
	
		lr_start_transaction("click_sign_off");
	
			web_revert_auto_header("Sec-Fetch-User");
		
			web_add_header("Sec-Fetch-User", 
				"?1");
		
			lr_think_time(5);
			
			web_reg_find("Fail=NotFound",
				"Text= A Session ID has been created and loaded into a cookie called MSO",
				LAST);
		
			web_url("SignOff Button", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
				"Snapshot=t5.inf", 
				"Mode=HTML", 
				LAST);
	
		lr_end_transaction("click_sign_off",LR_AUTO);

	lr_end_transaction("01_FindFlight",LR_AUTO);

	return 0;
}