/// A custom build.rs for building out the isis-iobc-supervisor
/// yotta module and exporting it as a Rust crate

fn main() {
    cubeos_build_helper::build_module();
}
