//
//  EaseChatViewController.h
//  EaseIM
//
//  Created by XieYajie on 2019/1/18.
//  Update © 2020 zhangchong. All rights reserved.
//



#import "EaseChatViewModel.h"
#import "EaseChatViewControllerDelegate.h"

NS_ASSUME_NONNULL_BEGIN

@interface EaseChatViewController : UIViewController <UIDocumentInteractionControllerDelegate>

@property (nonatomic, weak) id<EaseChatViewControllerDelegate> delegate;

@property (nonatomic, strong) EMConversation *currentConversation;
@property (nonatomic, strong) UITableView *tableView;
@property (nonatomic, strong) NSMutableArray *dataArray;
@property (nonatomic, strong) NSString *moreMsgId;  //第一条消息的消息id
@property (nonatomic) NSTimeInterval msgTimelTag;   //消息时间格式化

- (instancetype)initWithConversationId:(NSString *)aConversationId
                      conversationType:(EMConversationType)aType
                         chatViewModel:(EaseChatViewModel *)aModel;
//重置聊天控制器
- (void)resetChatVCWithViewModel:(EaseChatViewModel *)viewModel;

//是否显示输入状态
- (void)setEditingStatusVisible:(BOOL)editingStatusVisible;
//发送文本消息
- (void)sendTextAction:(NSString *)aText ext:(NSDictionary * __nullable)aExt;
//发送消息体
- (void)sendMessageWithBody:(EMMessageBody *)aBody ext:(NSDictionary * __nullable)aExt;
//消息已读回执
- (void)returnReadReceipt:(EMMessage *)msg;
//刷新页面 isScrollBottom：列表是否滚动到底部（最新一条消息处）
- (void)refreshTableView:(BOOL)isScrollBottom;
//填充数据刷新页面  isScrollBottom：列表是否滚动到底部（最新一条消息处）
- (void)refreshTableViewWithData:(NSArray<EMMessage *> *)messages isScrollBottom:(BOOL)isScrollBottom;
//清除从聊天页弹出的其他控制器页面(例：发起/接收 音视频通话时清理 相册弹出页/图片浏览页/输入扩展区收起等)
- (void)cleanPopupControllerView;
//停止音频播放
- (void)stopAudioPlayer;

@end

NS_ASSUME_NONNULL_END
