#include <ioutils.hpp>
#include <catch2/catch.hpp>
#include <filesystem>

using namespace sivox;
namespace fs = std::filesystem;

TEST_CASE("IOUtils : Write and read text files", "[io][files]") {
    using Catch::Equals;

    fs::path path = "ioutils_rw_text.txt";
    if (fs::exists(path) && fs::is_regular_file(path)) { fs::remove(path); }
    REQUIRE(!fs::exists(path));

    std::string text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse lacinia sem elit, at congue mauris feugiat ut. Aenean non tellus vel ipsum pretium dapibus sit amet eget mauris. Vestibulum viverra sed dolor ut laoreet. Pellentesque ullamcorper, urna id blandit feugiat, sem velit finibus urna, eu gravida justo lectus a lacus. Nullam in urna elit. In risus dui, aliquet in est efficitur, ultricies porta metus.  Integer egestas, risus a ultricies tristique, orci tortor ultrices felis, non tincidunt diam nisi quis libero.  Ut nec rhoncus dolor, eu pretium neque. Vivamus massa tellus, euismod sit amet ultricies vel, ultrices vel eros.  Ut ac enim ac tortor tempus congue.  Donec aliquet posuere tempor. Vivamus ligula mauris, hendrerit non scelerisque id, mattis sit amet nisl. Aliquam a malesuada tellus. Nullam ac lectus ut sem rhoncus vulputate nec consectetur quam. Pellentesque interdum lacus nibh, id venenatis ligula viverra in. Pellentesque congue at metus in auctor. Curabitur a leo quis massa efficitur ullamcorper. Donec eget orci venenatis, bibendum quam a, accumsan magna. Duis porttitor viverra feugiat.  Vestibulum pretium eget erat in laoreet. Praesent a tincidunt mi. Phasellus et faucibus dui. Integer eu dui at nibh condimentum sagittis. Fusce non rhoncus sem. Mauris ut dictum enim. Interdum et malesuada fames ac ante ipsum primis in faucibus. Fusce ac odio dapibus, iaculis quam quis, tincidunt neque. Nam nec lorem et tellus cursus dignissim in vel ex. Nullam consequat tempor justo. Donec in efficitur ipsum, at rhoncus est. Aliquam id enim id purus euismod tempor sed at sem. Nunc ut tortor eget enim vestibulum imperdiet quis et turpis.  In ut erat ut est lacinia congue. Duis ac suscipit tellus, sit amet pellentesque nulla. Duis facilisis id felis sed aliquam.  Vestibulum rutrum tortor vel velit vulputate gravida. Mauris at justo sagittis, volutpat odio non, mattis ex. Sed enim purus, laoreet vitae urna vitae, interdum mollis libero. Sed varius gravida magna ac euismod. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Nulla in odio id ex dapibus tristique. Mauris vehicula euismod consectetur. Aenean porta augue id urna pretium, sit amet tincidunt nibh bibendum. Duis sagittis ligula non sodales molestie.  Ut lacinia et sapien vitae lobortis. Nam sagittis augue ut dui mollis congue. Maecenas hendrerit velit quam, eu volutpat quam pulvinar sed. In eget mi nec quam blandit hendrerit. Etiam dui nisi, aliquet in nunc at, malesuada tincidunt libero. Curabitur in mauris feugiat, interdum purus et, tempor mauris. Vivamus pretium varius lorem, eu pellentesque risus. Nullam in varius ipsum. Aenean eget massa ac lectus rutrum convallis.  Praesent eget tincidunt purus. Nullam libero sem, convallis at iaculis ut, fermentum in ante. Integer tempor risus eget viverra viverra."; 

    write_text_file(path.string(), text);
    REQUIRE(fs::exists(path));
	REQUIRE(fs::is_regular_file(path));

    std::string readback = read_text_file(path.string());
    REQUIRE_THAT(readback, Equals(text));

    if (fs::exists(path) && fs::is_regular_file(path)) { fs::remove(path); }
}

TEST_CASE("IOUtils : Read text file that does not exist", "[io][files]") {
    using Catch::Equals;

    fs::path path = "fake_file.txt";
    REQUIRE(!fs::exists(path));

    std::string text = read_text_file(path.string());
    REQUIRE_THAT(text, Equals(""));
}
