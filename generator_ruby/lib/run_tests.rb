require "./generator_add.rb"
require "./generator_subtract.rb"
require "./generator_multiply.rb"
require "./generator_fract.rb"
require "./generator_floor_fp.rb"


puts "=== Generating adds tests ==="
gen = GeneratorAdd.new({"test_file_name" => "8_8/add.test", "saturated" => false  , "type" => "8_8", "title" => "8_8 add"});
gen.make_tests()
gen = GeneratorAdd.new({"test_file_name" => "8_8/saturated_add.test", "saturated" => true  , "type" => "8_8", "title" => "Saturated 8_8 add"});
gen.make_tests()
gen = GeneratorAdd.new({"test_file_name" => "16_16/add.test", "saturated" => false  , "type" => "16_16", "title" => "16_16 add"});
gen.make_tests()
gen = GeneratorAdd.new({"test_file_name" => "16_16/saturated_add.test", "saturated" => true  , "type" => "16_16", "title" => "Saturated 16_16 add"});
gen.make_tests()
gen = GeneratorAdd.new({"test_file_name" => "8_24/add.test", "saturated" => false  , "type" => "8_24", "title" => "8_24 add"});
gen.make_tests()
gen = GeneratorAdd.new({"test_file_name" => "8_24/saturated_add.test", "saturated" => true  , "type" => "8_24", "title" => "Saturated 8_24 add"});
gen.make_tests()
gen = GeneratorAdd.new({"test_file_name" => "24_8/add.test", "saturated" => false  , "type" => "24_8", "title" => "24.8 add"});
gen.make_tests()
gen = GeneratorAdd.new({"test_file_name" => "24_8/saturated_add.test", "saturated" => true  , "type" => "24_8", "title" => "Saturated 24.8 add"});
gen.make_tests()

puts "=== Generating subtract tests ==="
gen = GeneratorSubtract.new({"test_file_name" => "8_8/subtract.test", "saturated" => false  , "type" => "8_8", "title" => "8_8 subtract"});
gen.make_tests()
gen = GeneratorSubtract.new({"test_file_name" => "8_8/saturated_subtract.test", "saturated" => true  , "type" => "8_8", "title" => "Saturated 8_8 subtract"});
gen.make_tests()
gen = GeneratorSubtract.new({"test_file_name" => "16_16/subtract.test", "saturated" => false  , "type" => "16_16", "title" => "16_16 subtract"});
gen.make_tests()
gen = GeneratorSubtract.new({"test_file_name" => "16_16/saturated_subtract.test", "saturated" => true  , "type" => "16_16", "title" => "Saturated 16_16 subtract"});
gen.make_tests()
gen = GeneratorSubtract.new({"test_file_name" => "8_24/subtract.test", "saturated" => false  , "type" => "8_24", "title" => "8_24 subtract"});
gen.make_tests()
gen = GeneratorSubtract.new({"test_file_name" => "8_24/saturated_subtract.test", "saturated" => true  , "type" => "8_24", "title" => "Saturated 8_24 subtract"});
gen.make_tests()
gen = GeneratorSubtract.new({"test_file_name" => "24_8/subtract.test", "saturated" => false  , "type" => "24_8", "title" => "24.8 subtract"});
gen.make_tests()
gen = GeneratorSubtract.new({"test_file_name" => "24_8/saturated_subtract.test", "saturated" => true  , "type" => "24_8", "title" => "Saturated 24.8 subtract"});
gen.make_tests()

puts "=== Generating multiply tests ==="
gen = GeneratorMultiply.new({"test_file_name" => "8_8/multiply.test", "saturated" => false  , "type" => "8_8", "title" => "8_8 multiply"});
gen.make_tests()
gen = GeneratorMultiply.new({"test_file_name" => "8_8/saturated_multiply.test", "saturated" => true  , "type" => "8_8", "title" => "Saturated 8_8 multiply"});
gen.make_tests()
gen = GeneratorMultiply.new({"test_file_name" => "16_16/multiply.test", "saturated" => false  , "type" => "16_16", "title" => "16_16 multiply"});
gen.make_tests()
gen = GeneratorMultiply.new({"test_file_name" => "16_16/saturated_multiply.test", "saturated" => true  , "type" => "16_16", "title" => "Saturated 16_16 multiply"});
gen.make_tests()
gen = GeneratorMultiply.new({"test_file_name" => "8_24/multiply.test", "saturated" => false  , "type" => "8_24", "title" => "8_24 multiply"});
gen.make_tests()
gen = GeneratorMultiply.new({"test_file_name" => "8_24/saturated_multiply.test", "saturated" => true  , "type" => "8_24", "title" => "Saturated 8_24 multiply"});
gen.make_tests()
gen = GeneratorMultiply.new({"test_file_name" => "24_8/multiply.test", "saturated" => false  , "type" => "24_8", "title" => "24.8 multiply"});
gen.make_tests()
gen = GeneratorMultiply.new({"test_file_name" => "24_8/saturated_multiply.test", "saturated" => true  , "type" => "24_8", "title" => "Saturated 24.8 multiply"});
gen.make_tests()

puts "=== Generating floor tests ==="
gen = GeneratorFloorFp.new({"test_file_name"=>"8_8/integer_part.test","title"=>"8.8 floor test","type"=>"8_8"});
gen.make_tests()
gen = GeneratorFloorFp.new({"test_file_name"=>"8_24/integer_part.test","title"=>"8.24 floor test","type"=>"8_24"});
gen.make_tests()
gen = GeneratorFloorFp.new({"test_file_name"=>"16_16/integer_part.test","title"=>"16.16 floor test","type"=>"16_16"});
gen.make_tests()
gen = GeneratorFloorFp.new({"test_file_name"=>"24_8/integer_part.test","title"=>"24.8 floor test","type"=>"24_8"});
gen.make_tests()

puts "=== Generating fract tests ==="
gen = GeneratorFract.new({"test_file_name"=>"8_8/fractional.test","title"=>"8.8 fractional test","type"=>"8_8"});
gen.make_tests()
gen = GeneratorFract.new({"test_file_name"=>"8_24/fractional.test","title"=>"8.24 fractional test","type"=>"8_24"});
gen.make_tests()
gen = GeneratorFract.new({"test_file_name"=>"16_16/fractional.test","title"=>"16.16 fractional test","type"=>"16_16"});
gen.make_tests()
gen = GeneratorFract.new({"test_file_name"=>"24_8/fractional.test","title"=>"24.8 fractional test","type"=>"24_8"});
gen.make_tests()


puts "=== Finished ==="