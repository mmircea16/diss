require "./generator_divide.rb"
require "./generator_sqrt.rb"
require "./generator_log.rb"
require "./generator_exp.rb"

puts "=== Generating divide tests ==="
gen = GeneratorDivide.new({"test_file_name" => "8_8/divide.test", "saturated" => false  , "type" => "8_8", "title" => "8_8 divide"});
gen.make_tests()
gen = GeneratorDivide.new({"test_file_name" => "16_16/divide.test", "saturated" => false  , "type" => "16_16", "title" => "16_16 divide"});
gen.make_tests()
gen = GeneratorDivide.new({"test_file_name" => "8_24/divide.test", "saturated" => false  , "type" => "8_24", "title" => "8_24 divide"});
gen.make_tests()
gen = GeneratorDivide.new({"test_file_name" => "24_8/divide.test", "saturated" => false  , "type" => "24_8", "title" => "24.8 divide"});
gen.make_tests()

puts "=== Generating sqrt tests ==="
gen = GeneratorSqrt.new({"test_file_name" => "8_8/sqrt.test", "saturated" => false  , "type" => "8_8", "title" => "8_8 sqrt"});
gen.make_tests()
gen = GeneratorSqrt.new({"test_file_name" => "16_16/sqrt.test", "saturated" => false  , "type" => "16_16", "title" => "16_16 sqrt"});
gen.make_tests()
gen = GeneratorSqrt.new({"test_file_name" => "8_24/sqrt.test", "saturated" => false  , "type" => "8_24", "title" => "8_24 sqrt"});
gen.make_tests()
gen = GeneratorSqrt.new({"test_file_name" => "24_8/sqrt.test", "saturated" => false  , "type" => "24_8", "title" => "24.8 sqrt"});
gen.make_tests()

puts "=== Generating log tests ==="
gen = GeneratorLog.new({"test_file_name" => "8_8/log.test", "saturated" => false  , "type" => "8_8", "title" => "8_8 log"});
gen.make_tests()
gen = GeneratorLog.new({"test_file_name" => "16_16/log.test", "saturated" => false  , "type" => "16_16", "title" => "16_16 log"});
gen.make_tests()
gen = GeneratorLog.new({"test_file_name" => "8_24/log.test", "saturated" => false  , "type" => "8_24", "title" => "8_24 log"});
gen.make_tests()
gen = GeneratorLog.new({"test_file_name" => "24_8/log.test", "saturated" => false  , "type" => "24_8", "title" => "24.8 log"});
gen.make_tests()

puts "=== Generating exp tests ==="
gen = GeneratorExp.new({"test_file_name" => "8_8/exp.test", "saturated" => false  , "type" => "8_8", "title" => "8_8 exp"});
gen.make_tests()
gen = GeneratorExp.new({"test_file_name" => "16_16/exp.test", "saturated" => false  , "type" => "16_16", "title" => "16_16 exp"});
gen.make_tests()
gen = GeneratorExp.new({"test_file_name" => "8_24/exp.test", "saturated" => false  , "type" => "8_24", "title" => "8_24 exp"});
gen.make_tests()
gen = GeneratorExp.new({"test_file_name" => "24_8/exp.test", "saturated" => false  , "type" => "24_8", "title" => "24.8 exp"});
gen.make_tests()