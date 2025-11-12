%undefine _enable_debug_packages
Name:           fast_git_grep
Version:        1.0.2
Release:        1%{?dist}
Summary:        Fast git grep utility for GitLab hashed repositories

License:        MIT
URL:            https://example.com/fast_git_grep
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  gcc, make
Requires:       git

%description
A fast grep utility using git grep for all projects in GitLab's @hashed repositories.

%prep
%setup -q

%build
make


%install
mkdir -p %{buildroot}/usr/sbin
mkdir -p %{buildroot}/etc/%{name}
install -m 0755 fast_git_grep %{buildroot}/usr/sbin/fast_git_grep
install -m 0644 etc/ini.config %{buildroot}/etc/%{name}/ini.config


%files
/usr/sbin/fast_git_grep
/etc/%{name}/ini.config

%changelog
* Fri Aug 29 2025 Your Name <your.email@example.com> - 1.0-1
- Initial RPM release

* Wed Nov 12 2025 Satoshi Kaneko <secret@example.com> - 1.0.2
- Add Project Cache 