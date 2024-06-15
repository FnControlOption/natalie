require 'minitest/spec'
require 'minitest/autorun'
require 'time'
require 'timeout'
require_relative '../support/nat_binary'

describe 'ruby/spec' do
  parallelize_me!

  def spec_timeout
    (ENV['SPEC_TIMEOUT'] || 120).to_i
  end

  Dir.chdir File.expand_path('../..', __dir__)
  glob = if ENV['DEBUG_COMPILER']
           # I use this when I'm working on the compiler,
           # as it catches 99% of bugs and finishes a lot quicker.
           Dir['spec/language/*_spec.rb']
         elsif (glob = ENV['GLOB']).to_s.size.positive?
           # GLOB="spec/core/io/*_spec.rb,spec/core/thread/*_spec.rb" rake test
           Dir[*glob.split(',')].tap do |files|
             puts "Matched files:"
             puts files.to_a
           end
         else
           Dir['spec/**/*_spec.rb']
         end
  glob.each do |path|
    describe path do
      it 'passes all specs' do
        out_nat = Timeout.timeout(spec_timeout, nil, "execution expired running: #{path}") do
          `#{NAT_BINARY} #{path} 2>&1`
        end
        puts out_nat if ENV['DEBUG'] || !$?.success?
        expect($?).must_be :success?
        expect(out_nat).wont_match(/traceback|error/i)
      end
    end
  end
end
