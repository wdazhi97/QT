from django.db import models

# Create your models here.
class user(models.Model):
	name=models.CharField(max_length=20)
	phone=models.CharField(max_length=11)
	email=models.CharField(max_length=40)
	password=models.CharField(max_length=20,null=True)
	def __str__(self):
		return self.name