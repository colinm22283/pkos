{
  description = "PKArch Developement Flake";

  inputs = {
    nixpkgs.url = "nixpkgs/nixos-26.05";
    utils.url = "github:numtide/flake-utils";

    pkos_binutils_flake.url = "git+ssh://git@pksrv:/git/pkos_binutils.git?rev=c3b3e890d00cdedfbfafb70b06beb428c4b195bd&shallow=1";
    pkos_gcc_flake.url = "git+ssh://git@pksrv:/git/pkos_gcc.git?rev=4d2e320e39c7effd1296f0764f34b20939680688&shallow=1";
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

            i686Pkgs.buildPackages.gcc
            i686Pkgs.buildPackages.binutils

            x64Pkgs.buildPackages.gcc
            x64Pkgs.buildPackages.binutils

            pkos_binutils
            pkos_gcc
          ];
        };
      });
}

