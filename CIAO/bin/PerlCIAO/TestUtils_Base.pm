#File generated by C:\ACE_wrappers_devel\ACE_wrappers\TAO\CIAO\bin\PerlCIAO\generate_container.pl.
#Input file: TestUtils.base.
#Code generator author: Stoyan Paunov
#

#class TestUtils_Base
package TestUtils_Base;
use strict;

#Class constructor :)
sub new {
    my ($class) = @_;

    #Create a reference to an anonymous hash
    my $self = {
        _processes        => undef,
        _files            => undef,
        _wd               => undef
     };

    #Bless the hash.
    bless $self, $class;
    return $self;
}

#accessor/mutator method for processes
sub processes {
    my ( $self, $processes ) = @_;

    $self->{_processes} = $processes
         if defined ($processes);

    return $self->{_processes};
}

#accessor/mutator method for files
sub files {
    my ( $self, $files ) = @_;

    $self->{_files} = $files
         if defined ($files);

    return $self->{_files};
}

#accessor/mutator method for wd
sub wd {
    my ( $self, $wd ) = @_;

    $self->{_wd} = $wd
         if defined ($wd);

    return $self->{_wd};
}

#print method for the class
sub print {
    my ($self) = @_;

    my $f;

    $f = defined ($self->{_processes})
          ? $self->{_processes} : "not defined";
    printf ("processes: %s\n", $f);

    $f = defined ($self->{_files})
          ? $self->{_files} : "not defined";
    printf ("files: %s\n", $f);

    $f = defined ($self->{_wd})
          ? $self->{_wd} : "not defined";
    printf ("wd: %s\n", $f);

}

#class return value
1;
