function register(){
	var user = document.getElementById("username").value;
	var pass = document.getElementById("password").value;
	var cpass = document.getElementById("cpassword").value;
	if (pass == cpass){
		$.ajax({
			type: 'POST',
			url: '/h4x0rzServlet/Register',
			data:{
				username: user,
				password: cpass
			},
			success:function(data){
				alert(data);
			}
		});
	}else{
		alert("Passwords do not match.");
	}
}