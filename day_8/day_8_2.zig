const std = @import("std");

pub fn main() !void {
    var file = try std.fs.cwd().openFile("input.txt", .{});

    defer file.close();

    var buf_reader = std.io.bufferedReader(file.reader());
    var in_stream = buf_reader.reader();

    var buf: [1024]u8 = undefined;
    const maybe_directions = try in_stream.readUntilDelimiterOrEof(&buf, '\n');
    if (maybe_directions) |directions_raw| {
        var gpa = std.heap.GeneralPurposeAllocator(.{}){};
        const allocator = gpa.allocator();
        const directions = try allocator.dupe(u8, directions_raw);
        std.debug.print("directions: {s}\n", .{directions});

        const Ways = struct { l: []const u8, r: []const u8 };
        var map = std.StringHashMap(Ways).init(allocator);

        while (try in_stream.readUntilDelimiterOrEof(&buf, '\n')) |line| {
            if (line.len > 0) {
                const key = try allocator.dupe(u8, line[0..3]);
                const lval = try allocator.dupe(u8, line[7..10]);
                const rval = try allocator.dupe(u8, line[12..15]);

                try map.put(key, .{ .l = lval, .r = rval });
                //std.debug.print("# {s}\n", .{line});
            }
        }

        var head: []const u8 = "AAA";
        if (map.get(head)) |ways_ptr| {
            var ways = ways_ptr;
            var i: usize = 0;
            var counter: usize = 0;
            while (!std.mem.eql(u8, head, "ZZZ")) : (i = @mod(i + 1, directions.len)) {
                std.debug.print("Dir: {c} - ", .{directions[i]});
                if (directions[i] == 'L') {
                    head = ways.l;
                    counter += 1;
                } else if (directions[i] == 'R') {
                    head = ways.r;
                    counter += 1;
                } else {
                    std.debug.print("Couldn't read direction ({c})\n", .{directions[i]});
                }
                if (map.get(head)) |ways_p| {
                    ways = ways_p;
                } else {
                    std.debug.print("Key not found in map: {s}\n", .{head});
                    break;
                }
                std.debug.print("New Head: {s}\n", .{head});
            }
            std.debug.print("Steps: {d}\n", .{counter});
        } else {
            std.debug.print("Key not found in map: {s}\n", .{head});
        }

        var entry_it = map.iterator();
        while (entry_it.next()) |entry| {
            allocator.free(entry.key_ptr.*); // Free the key
            allocator.free(entry.value_ptr.*.l); // Free left string
            allocator.free(entry.value_ptr.*.r);
        }
        map.deinit();
        allocator.free((directions));
        const gpa_result = gpa.deinit();
        if (gpa_result != .ok) {
            std.debug.print("Memory leak detected!\n", .{});
        }
    } else {
        std.debug.print("No directions line found!\n", .{});
    }
}
