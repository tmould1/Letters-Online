/************************************************/
/*
/* Filename: Client.js
/*
/* Purpose: contains a list of functions for the web client 
/*  		to interact dynamically with the server
/*
/* Author: Ryan Ngo
/*
/* Change Log:
/* {Date}: {Description}
/* 10/24/16: add register and login function
/*
/************************************************/
function register(){
	var user = document.getElementById("username").value;
	var pass = document.getElementById("password").value;
	var cpass = document.getElementById("cpassword").value;
	if (user != "" && pass != ""){
		if (pass == cpass){
			$.ajax({
				type: 'POST',
				url: '/h4x0rzServlet/Register',
				data:{
					username: user,
					password: pass
				},
				success:function(data){
					alert(data);
				}
			});
		}else{
			alert("Passwords do not match.");
		}
	}else{
		alert("username or password cannot be blank.");
	}
	
}

function login(){
	var user = document.getElementById("username").value;
	var pass = document.getElementById("password").value;
	if (user != "" && pass != ""){
		$.ajax({
			type: 'POST',
			url: '/h4x0rzServlet/Login',
			data:{
				username: user,
				password: pass
			},
			success:function(data){
				if (data == "true"){
					alert("Successful login.");
				}else if (data == "false"){
					alert("Failed login. Incorrect password.");
				}else{
					alert("Failed login. User not registered.");
				}
			}
		});
	}else{
		alert("username or password cannot be blank.");
	}
}