Name:           fast_git_grep
Version:        1.0
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
mkdir -p %{buildroot}/usr/bin
install -m 0755 fast_git_grep %{buildroot}/usr/bin/fast_git_grep

%files
/usr/bin/fast_git_grep

%changelog
* Wed Aug 28 2025 Your Name <your.email@example.com> - 1.0-1
- Initial RPM release