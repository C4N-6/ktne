{
  pkgs ? import <nixpkgs> { },
}:

pkgs.stdenv.mkDerivation {
  name = "my-project";
  src = ./.;
  nativeBuildInputs = with pkgs; [
    gnumake
    gcc
    pkg-config
  ];
  buildInputs = with pkgs; [
    ncurses
  ];
}
