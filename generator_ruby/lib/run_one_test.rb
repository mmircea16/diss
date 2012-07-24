require "./generator_sqrt.rb"
require "./generator_subtract.rb"
require "./generator_multiply.rb"
require "./generator_fract.rb"
require "./generator_floor_fp.rb"
require "./generator_divide.rb"
require "./generator_log.rb"

puts "=== Start ==="
gen = GeneratorLog.new({"test_file_name" => "24_8/log.test", "saturated" => false  , "type" => "24_8", "title" => "24_8 log"});
gen.make_tests()
puts "=== Finish ==="
