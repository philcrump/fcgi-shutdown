fcgi-shutdown
==========
Simple FastCGI application to issue shutdown command (and potentially perform other tasks in the future).

Authentication is assumed to be implemented at an earlier stage (eg. HTTP auth)

## Dependencies

apt install libfcgi-dev

## Example Nginx config with PAM (System User) Authentication

`# sudo usermod -a -G shadow www-data`

_/etc/pam.d/nginx_
```
@include common-auth
```

_/etc/nginx/conf.d/<site>.conf_
```
...

location /postShutdown {
  if ( $request_method !~ ^(POST)$ ) {
    return 405;
  }
  
  auth_pam    "Command Authorisation";
  auth_pam_service_name   "nginx";
  
  include /etc/nginx/fastcgi_params;
  fastcgi_param FN_HANDLER postShutdown;
  fastcgi_pass 127.0.0.1:2005;
}

...
```