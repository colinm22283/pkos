{
  description = "PKArch Developement Flake";

  inputs = {
    nixpkgs.url = "nixpkgs/nixos-26.05";
    utils.url = "github:numtide/flake-utils";

    pkos_binutils_flake.url = "git+https://cmcgann.com/githttp/pkos_binutils.git?rev=ab1dce2aa5c3a1e15034cef21134b3fb063d56e3&shallow=1";
    pkos_gcc_flake.url = "git+https://cmcgann.com/githttp/pkos_gcc.git?rev=69b488c2b1cd85876f665eec6ca78ae5d41a7bd2&shallow=1";
  };

  outputs = { self, nixpkgs, utils, pkos_binutils_flake, pkos_gcc_flake }:
    utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
        
        i686Pkgs = pkgs.pkgsCross.i686-embedded;
        x64Pkgs = pkgs.pkgsCross.x86_64-embedded;

        pkos_binutils = pkos_binutils_flake.packages.${pkgs.system}.default;
        pkos_gcc = pkos_gcc_flake.packages.${pkgs.system}.default;
      in
      {
        devShells.default = pkgs.mkShell {
          buildInputs = [
            pkgs.qemu
            pkgs.gdb

            i686Pkgs.buildPackages.gcc
            i686Pkgs.buildPackages.binutils

            x64Pkgs.buildPackages.gcc
            x64Pkgs.buildPackages.binutils
            x64Pkgs.buildPackages.gdb

            pkos_binutils
            pkos_gcc
          ];
        };
      });
}

