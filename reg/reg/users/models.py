from django.contrib.auth.models import AbstractBaseUser, PermissionsMixin
from django.contrib.contenttypes.models import ContentType
from django.core.mail import send_mail
from django.db import models
from django.utils import timezone
from django.utils.translation import ugettext_lazy as _

from .conf import settings
from .managers import UserInheritanceManager, UserManager


class AbstractUser(AbstractBaseUser, PermissionsMixin):
    USERS_AUTO_ACTIVATE = not settings.USERS_VERIFY_EMAIL
    sex=models.CharField(_('性别'),max_length=6,null=True)
    phonenumber=models.CharField(_('手机号码'),max_length=11,null=True)
    name=models.CharField(_('用户名'),max_length=30,null=True,unique=True)
    realname=models.CharField(_('姓名'),max_length=30,null=True)
    email = models.EmailField(
        _('邮箱'), max_length=255, unique=True, db_index=True) #邮箱
    email2 = models.EmailField(_('备用邮箱'),max_length=255,unique=True,null=True)
    officephone=models.CharField(_('办公电话'),max_length=11,unique=True,null=True)
    job=models.CharField(_('职称'),max_length=30,null=True)
    workunit=models.CharField(_('工作单位'),max_length=255,null=True)
    address=models.CharField(_('通讯地址'),max_length=255,null=True)
    postcode=models.CharField(_('邮编'),max_length=6,null=True)
    is_staff = models.BooleanField(
        _('staff status'), default=False,
        help_text=_('Designates whether the user can log into this admin site.')) #能进入管理台才能更改

    is_active = models.BooleanField(
        _('active'), default=USERS_AUTO_ACTIVATE,
        help_text=_('Designates whether this user should be treated as '
                    'active. Unselect this instead of deleting accounts.')) #是否激活
    date_joined = models.DateTimeField(_('date joined'), default=timezone.now) #注册日期
    user_type = models.ForeignKey(ContentType, null=True, editable=False) #用户类型

    objects = UserInheritanceManager()
    base_objects = UserManager()

    USERNAME_FIELD = 'email'
    REQUIRED_FIELDS = []

    class Meta:
        verbose_name = _('User')
        verbose_name_plural = _('Users')
        abstract = True

    def get_full_name(self):
        """ Return the email."""
        return self.email

    def get_short_name(self):
        """ Return the email."""
        return self.email

    def email_user(self, subject, message, from_email=None):
        """ Send an email to this User."""
        send_mail(subject, message, from_email, [self.email])

    def activate(self):
        self.is_active = True
        self.save()

    def save(self, *args, **kwargs):
        if not self.user_type_id:
            self.user_type = ContentType.objects.get_for_model(self, for_concrete_model=False)
        super(AbstractUser, self).save(*args, **kwargs)


class User(AbstractUser):

    """
    Concrete class of AbstractUser.
    Use this if you don't need to extend User.
    """

    class Meta(AbstractUser.Meta):
        swappable = 'AUTH_USER_MODEL'
class bill(models.Model):
    user=models.ForeignKey(User)
    billhead=models.CharField(_('发票抬头'),max_length=30)
    billnumber=models.CharField(_('税务号'),max_length=30)
    phone=models.CharField(_('电话'),max_length=11,null=True)
    address=models.CharField(_('地址'),null=True,max_length=30)
    bank=models.CharField(_('开户行'),null=True,max_length=30)
    accountnumber=models.CharField(_('账号'),null=True,max_length=30)
    class Meta:
        verbose_name=_('发票')
        verbose_name_plural = _('发票')
class Internetrecord(models.Model):
    user=models.ForeignKey(User,null=True)
    time=models.DateTimeField(_('访问时间'),auto_now_add=True)
    page=models.URLField(_('访问页面'))
    IP=models.GenericIPAddressField(_('访问IP'))
    comment=models.CharField(_('备注'),max_length=255,null=True)
class pay(models.Model):
    user=models.ForeignKey(User)
    paycompany=models.CharField(_('缴费单位名称'),max_length=30)
    paytime=models.DateField(_('缴费时间'))
    payaccount=models.CharField(_('缴费账号'),max_length=30)
    remark=models.CharField(_('备注'),max_length=50)
    creditfile=models.FileField(_('凭证文件'))
    class Meta:
        verbose_name=_('缴费记录')
        verbose_name_plural=_('缴费记录')