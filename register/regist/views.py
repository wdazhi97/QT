from django.shortcuts import render
from regist import models
# Create your views here.
def register(request):
	return render(request, 'reg.html')
def reg(request):
	if request.POST:
		inputname=request.POST['name']
		inputphone=request.POST['phone']
		inputemail=request.POST['email']
		inputpd=request.POST['passwd']
		inputpdag=request.POST['pdagain']
	if models.user.objects.filter(name=inputname).exists():
		message="该用户已存在"
	elif models.user.objects.filter(phone=inputphone).exists():
		message="该电话已被使用"
	elif models.user.objects.filter(email=inputemail).exists():
		message="该邮箱已被使用"
	elif inputpd!=inputpdag:
		message="密码两次不匹配"
	elif inputname=="":
		message="用户名不能为空"
	elif inputphone=="":
		message="电话号码不能为空"
	elif inputemail=="":
		message="邮箱不能为空"
	elif inputpd=="":
		message="密码不能为空"
	elif inputpdag=="":
		message="请确认密码"
	else:
		models.user.objects.create(name=inputname,phone=inputphone,email=inputemail,password=inputpd)
		message="注册成功"
	return render(request, 'reg.html',{'message':message})
logmessage=""
def login(request):
	global logmessage
	if request.POST:
		global logmessage
		logname=request.POST['username']
		logpasswd=request.POST['userpsaaword']
		if models.user.objects.filter(name=logname).exists():
			u=models.user.objects.get(name=logname)
			if logpasswd==u.password:
				logmessage="登录成功"
			else:
				logmessage="密码错误"
		else:
			logmessage="用户不存在"
	return render(request,'login.html',{'message':logmessage})