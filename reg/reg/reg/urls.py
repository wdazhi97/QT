"""reg URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/dev/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  url(r'^$', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  url(r'^$', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.conf.urls import url, include
    2. Add a URL to urlpatterns:  url(r'^blog/', include('blog.urls'))
"""
from django.conf.urls import url,include
from django.contrib import admin
from django.conf import settings
from obj import views
from captcha import views as cap_views
from django.conf.urls.static import static
urlpatterns = [
    url(r'^admin/', admin.site.urls),
	url(r'^accounts/',include('users.urls')),
    url(r'^$',views.index,name='index'),
    url(r'^404$',views.page404,name='page404'),
    url(r'^captcha/', include('captcha.urls')),
] + static(settings.STATIC_URL, document_root = settings.STATIC_ROOT)
